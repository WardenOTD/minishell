/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/10 19:32:05 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*expand(t_lexer *input, t_env *env)
{
	t_lexer	*lhead;
	t_env	*ehead;
	int		i;
	int		j;
	int		flag;
	int		dflag;

	lhead = input;
	ehead = env;
	flag = 0;
	dflag = 0;
	while (lhead)
	{
		i = 0;
		while (lhead->arg[i])
		{
			j = 0;
			while (lhead->arg[i][j])
			{
				if (lhead->arg[i][j] == '\'')
				{
					if (flag == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (lhead->arg[i][j] == '"')
				{
					if (dflag == 0)
						dflag = 1;
					else
						dflag = 0;
				}
				if (lhead->arg[i][j] == '$' && flag == 0)
				{
					if (lhead->arg[i][j + 1] == ' ')
						j++;
					if (lhead->arg[i][j - 1] == '"' && lhead->arg[i][j - 1] == '"')
						j++;
				}
				j++;
			}
		}
	}
}
