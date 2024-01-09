/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 11:18:00 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*expand_helper_1(char *arg, t_env *env, int j)
{
	char	*to_replace;
	int		flag[4];

	to_replace = 0;
	set_arr_to_zero(flag, 4);
	while (arg[j])
	{
		if (arg[j] == '\'' || arg[j] == '\"')
			get_flag(flag, arg[j], j);
		if (yes_expand(arg[j], arg[j + 1]) && analyze_flag(flag))
		{
			to_replace = get_to_replace(arg, j);
			arg = replace_expand(arg, j, to_replace, env);
			set_arr_to_zero(flag, 4);
			j = 0;
			free(to_replace);
		}
		else
			j++;
	}
	return (arg);
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
