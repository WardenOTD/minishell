/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/19 19:50:13 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	call(t_lexer *input, t_env *env, t_exp *exp, char *line, char **envp)
{
	if (!ft_strncmp(input->arg[0], "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->arg[0], "env", 4))
		display_env(env);
	else if (!ft_strncmp(input->arg[0], "export", 7) && input->arg[1])
		export_get(input, env, exp);
	else if (!ft_strncmp(input->arg[0], "export", 7) && !input->arg[1])
		display_exp(exp);
	else if (!ft_strncmp(input->arg[0], "pwd", 5))
		ft_pwd();
	else if (!ft_strncmp(input->arg[0], "cd", 3))
		cd(input, env, envp);
	else if (!ft_strncmp(input->arg[0], "unset", 6))
		unset(input, env);
	else
		exec_bin(line, envp);
}
