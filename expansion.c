/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/03 14:51:40 by jteoh            ###   ########.fr       */
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
	int		flag;
	int		dflag;
	int		retv;

	flag = 0;
	dflag = 0;
	while (arg[j])
	{
		expand_flags_set(arg[j], &flag, &dflag);
		if ((arg[j] == '$' && flag == 0)
			|| (arg[j] == '$' && dflag == 1))
		{
			retv = expand_helper_if(&arg, j, flag, dflag);
			if (retv == 0)
				break ;
			else if (retv == -1)
				if (expand_helper_else_if(&arg, j, flag, dflag) == -1)
					expand_helper_else(&arg, env, j);
			expand_helper_purge(&j, &dflag, &flag);
			continue ;
		}
		j++;
	}
	return (arg);
}

void	expand_helper_purge(int *j, int *dflag, int *flag)
{
	*j = 0;
	*dflag = 0;
	*flag = 0;
}
