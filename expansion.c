/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 13:40:08 by jteoh            ###   ########.fr       */
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
	int		sflag;

	to_replace = NULL;
	sflag = 0;
	while (arg[j])
	{
		if (arg[j] == '\'')
			sflag++;
		if (yes_expand(arg[j], arg[j + 1]) && sflag % 2 == 0)
		{
			to_replace = get_to_replace(arg, j);
			arg = replace_expand(arg, to_replace, env);
			sflag = 0;
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
	if (c2 == ' ' || c2 == '$' || c2 == 0 || c2 == '\"' || c2 == '\'')
		return (0);
	return (1);
}

char	*get_to_replace(char *str, int pos)
{
	int		i;
	int		j;
	char	*ret;

	if (str[pos + 1] == '?')
		return (ft_strdup("$?"));
	i = pos + 1;
	j = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	ret = malloc (sizeof(char) * (i - pos + 1));
	while (pos < i)
	{
		ret[j++] = str[pos++];
	}
	ret[j] = 0;
	return (ret);
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
