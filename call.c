/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/19 16:21:30 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	execute_cmd(t_root *root, char **envp, t_fd_info *fd_info)
{
	if (handle_redirect(root->input->arg, fd_info) == -1)
		return ;
	root->input->arg = renew_arg_rm_redir(root->input->arg);
	call(root, envp);
	dup2(fd_info->saved_out_fd, 1);
	dup2(fd_info->saved_in_fd, 0);
}

void	call(t_root *root, char **envp)
{
	int	i;

	if (root->input == NULL)
		return ;
	if (call_builtins(root, envp) == 0)
	{
		if (exec_bin(root->input, envp) == -1)
		{
			i = 0;
			while (root->input->arg[i])
			{
				if (root->input->arg[i + 1])
					printf("%s ", root->input->arg[i]);
				else if (root->input->arg[i + 1] == 0)
					printf("%s", root->input->arg[i]);
				i++;
			}
			printf(": command not found\n");
		}
	}
}

int	call_builtins(t_root *root, char **envp)
{
	if (!ft_strncmp(root->input->arg[0], "echo", 5))
		echo(root->input);
	else if (!ft_strncmp(root->input->arg[0], "env", 4))
		display_env(root->env);
	else if (!ft_strncmp(root->input->arg[0], "export", 7) && root->input->arg[1])
		export_get(root->input, root->env, root->exp);
	else if (!ft_strncmp(root->input->arg[0], "export", 7) && !root->input->arg[1])
		display_exp(root->exp);
	else if (!ft_strncmp(root->input->arg[0], "pwd", 5))
		ft_pwd();
	else if (!ft_strncmp(root->input->arg[0], "cd", 3))
		cd(root->input, root->env, envp);
	else if (!ft_strncmp(root->input->arg[0], "unset", 6))
		unset(root->input, root->env);
	else
		return (0);
	return (1);
}
