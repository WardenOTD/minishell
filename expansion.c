/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 13:03:20 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*expand(t_lexer *input, t_env *env)
{
	t_lexer	*lhead;
	int		i;

	lhead = input;
	while (lhead)
	{
		i = 0;
		while (lhead->arg[i])
		{
			lhead->arg[i] = expand_helper_1(lhead->arg[i], env, 0);
			i++;
		}
		lhead = lhead->next;
	}
	return (input);
}

char	*expand_helper_1(char *arg, t_env *env, int j)
{
	char	*to_replace;
	int		flag[4];

	to_replace = NULL;
	set_arr_to_zero(flag, 4);
	while (arg[j])
	{
		if (arg[j] == '\'' || arg[j] == '\"')
			get_flag(flag, arg[j], j);
		if (yes_expand(arg[j], arg[j + 1]) && analyze_flag(flag))
		{
			if (yes_expand(arg[j], arg[j + 1]) == 2 && (flag[0] % 2 == 1 || flag[2] % 2 == 1)){
				j++;
				printf("here1\n");
				continue ;
			}
			if (yes_expand(arg[j], arg[j + 1]) == 2 && (flag[0] % 2 == 0 || flag[2] % 2 == 0)){
				to_replace = ft_strdup("$");
				printf("here2\n");}
			else
				to_replace = get_to_replace(arg, j);
			arg = replace_expand(arg, to_replace, env);
			set_arr_to_zero(flag, 4);
			j = 0;
			free(to_replace);
		}
		else
			j++;
	}
	return (arg);
}

int	yes_expand(char c1, char c2)
{
	if (c1 != '$')
		return (0);
	if (c2 == ' ' || c2 == '$' || c2 == 0)
		return (0);
	if (c2 == '\"' || c2 == '\'')
		return (2);
	return (1);
}

char	*replace_expand(char *str, char *to_r, t_env *env)
{
	char	*new_value;
	char	*ret;
	int		n_len;

	if (!ft_strncmp(to_r, "$?", 3))
		new_value = ft_itoa(g_status_code);
	else
		new_value = get_env_value(to_r, env);
	if (!new_value)
		n_len = 0;
	else
		n_len = ft_strlen(new_value);
	ret = malloc (sizeof(char) * (ft_strlen(str)
				- ft_strlen(to_r) + n_len + 1));
	ret[(ft_strlen(str) - ft_strlen(to_r) + n_len)] = 0;
	ret = replace_expand_helper(str, to_r, new_value, ret);
	if (new_value)
		free(new_value);
	free(str);
	return (ret);
}

void	set_arr_to_zero(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
}

void	get_flag(int *flag, char c, int pos)
{
	if (c == '\"')
	{
		flag[0] += 1;
		flag[1] = pos;
	}
	else
	{
		if (flag[0] % 2 == 0)
			flag[2] += 1;
		flag[3] = pos;
	}
}

int	analyze_flag(int *flag)
{
	if (flag[0] % 2 == 0 && flag[2] % 2 == 0)
		return (1);
	else if (flag[0] % 2 == 1 && flag[2] % 2 == 0)
		return (1);
	else if (flag[0] % 2 == 0 && flag[2] % 2 == 1)
		return (0);
	else if (flag[0] % 2 == 1 && flag[2] % 2 == 1)
		if (flag[1] < flag[3])
			return (1);
	return (0);
}
