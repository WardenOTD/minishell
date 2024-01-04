/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 13:18:55 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	execute_cmd(t_root *root, t_lexer *input,
	char **envp, t_fd_info *fd_info)
{
	if (handle_redirect(input->arg, fd_info) == -1)
		return ;
	input->arg = renew_arg_rm_redir(input->arg);
	call(root, input, envp);
	dup2(fd_info->saved_out_fd, 1);
	dup2(fd_info->saved_in_fd, 0);
}

void	call(t_root *root, t_lexer *input, char **envp)
{
	int	err_num;

	if (input == NULL || input->arg == NULL)
		return ;
	if (call_builtins(root, input, envp) == 0)
	{
		err_num = exec_bin(root, input);
		if (err_num == -1)
		{
			printf("%s: command not found\n", input->arg[0]);
			if (root->has_pipe == 1)
				exit(127);
			else
			{
				g_status_code = 127;
				return ;
			}
		}
		else if (err_num == -2)
			printf("Command '' not found\n");
	}
}

int	call_builtins(t_root *root, t_lexer *input, char **envp)
{
	if (!ft_strncmp(input->arg[0], "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->arg[0], "env", 4))
		display_env(root->env);
	else if (!ft_strncmp(input->arg[0], "export", 7) && root->input->arg[1])
		export_get(input, root->env, root->exp);
	else if (!ft_strncmp(input->arg[0], "export", 7) && !root->input->arg[1])
		display_exp(root->exp);
	else if (!ft_strncmp(input->arg[0], "pwd", 5))
		ft_pwd();
	else if (!ft_strncmp(input->arg[0], "cd", 3))
		cd(input, root->env, envp);
	else if (!ft_strncmp(input->arg[0], "unset", 6))
		unset(input, root->env);
	else
		return (0);
	g_status_code = 0;
	return (1);
}
