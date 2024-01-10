/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:29 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/10 13:30:38 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	export_get(t_lexer *input, t_env *env, t_exp *exp)
{
	int	i;

	(void)exp;
	i = 1;
	while (input->arg[i])
	{
		if (ft_isdigit(input->arg[i][0]) || has_slash(input->arg[i]) == 1)
		{
			printf("Minishell: export: `%s'", input->arg[i++]);
			printf(": not a valid identifier\n");
			continue ;
		}
		env = add_env(env, input->arg[i]);
		i++;
	}
}

int	has_slash(char *arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arr[i])
	{
		if (arr[i] == '=')
			flag = 1;
		if (ft_isalnum(arr[i]) == 0 && flag == 0)
			return (1);
		i++;
	}
	return (0);
}
