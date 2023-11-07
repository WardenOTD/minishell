/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:28:29 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:06:48 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	export_get(t_lexer *input, t_env *env, t_exp *exp)
{
	(void)exp;
	if (input->arg[2])
	{
		printf("export syntax error\n");
		return ;
	}
	env = add_env(env, input);
}

