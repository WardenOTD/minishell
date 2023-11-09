/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/09 16:04:18 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	call(t_lexer *input, t_env *env, t_exp *exp)
{
	if (input == NULL)
		return ;
	if (!ft_strncmp(input->arg[0], "echo", 5))
		echo(input);
	if (!ft_strncmp(input->arg[0], "env", 4))
		display_env(env);
	if (!ft_strncmp(input->arg[0], "export", 7) && input->arg[1])
		export_get(input, env, exp);
	if (!ft_strncmp(input->arg[0], "export", 7) && !input->arg[1])
		display_exp(exp);
	if (!ft_strncmp(input->arg[0], "pwd", 5))
		ft_pwd();
	if (!ft_strncmp(input->arg[0], "cd", 3))
		cd(input, env);
}
