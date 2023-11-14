/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:29 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/14 16:19:21 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	export_get(t_lexer *input, t_env *env, t_exp *exp)
{
	(void)exp;
	// if (input->arg[2])
	// {
	// 	printf("export syntax error\n");
	// 	return ;
	// }
	if (ft_isdigit(input->arg[1][0]) || has_slash(input->arg[1]) == 1)
	{
		printf("Minishell: export: `%s`: not a valid identifier\n", input->arg[1]);
		return ;
	}
	env = add_env(env, input);
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
		if (arr[i] == '/' || (arr[i] == ' ' && flag == 0))
			return (1);
		i++;
	}
	return (0);
}
