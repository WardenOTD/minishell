/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/21 20:54:47 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	execute_cmd(t_lexer *input, t_env *env, t_exp *exp, char **envp, t_fd_info *fd_info)
{
	if (handle_redirect(input->arg, fd_info) == -1)
		return ;
	input->arg = renew_arg_rm_redir(input->arg);
	call(input, env, exp, envp);
	dup2(fd_info->saved_out_fd, 1);
	dup2(fd_info->saved_in_fd, 0);
}

void	call(t_lexer *input, t_env *env, t_exp *exp, char **envp)
{
	int	i;
	int	err_num;

	if (input == NULL)
		return ;
	if (call_builtins(input, env, exp, envp) == 0)
	{
		err_num = exec_bin(input, envp);
		if (err_num == -1)
		{
			i = 0;
			while (input->arg[i])
			{
				if (input->arg[i + 1])
					printf("%s ", input->arg[i]);
				else if (input->arg[i + 1] == 0)
					printf("%s", input->arg[i]);
				i++;
			}
			printf(": command not found\n");
		}
		else if (err_num == -2)
			printf("Command '' not found\n");
	}
}

int	call_builtins(t_lexer *input, t_env *env, t_exp *exp, char **envp)
{
	if (!ft_strncmp(input->arg[0], "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->arg[0], "env", 4))
		display_env(env);
	else if (!ft_strncmp(input->arg[0], "export", 7) && input->arg[1])
		export_get(input, env, exp);
	else if (!ft_strncmp(input->arg[0], "export", 7) && !input->arg[1])
		display_exp(exp);
	else if (!ft_strncmp(input->arg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(input->arg[0], "cd", 3))
		cd(input, env, envp);
	else if (!ft_strncmp(input->arg[0], "unset", 6))
		unset(input, env);
	else
		return (0);
	return (1);
}
