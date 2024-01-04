/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:04:19 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:26:33 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	pipe_err(t_root *root, char *line)
{
	root->input = freelexer(root->input);
	root->exp = free_exp(root->exp);
	free(line);
	printf("Fork Fail\n");
	exit(2);
}

void	pipe_var_init(t_root *root)
{
	root->pipe.pid = 1;
	root->pipe.fd_last[0] = -1;
	root->pipe.fd_last[1] = -1;
	root->pipe.count = 0;
	root->pipe.total_count = 0;
}

pid_t	pipe_init(t_root *root, char *line, t_fd_info *fd_info)
{
	t_lexer	*head;

	pipe_var_init(root);
	head = root->input;
	while (head != NULL)
	{
		root->pipe.count++;
		pipe_init_helper(head, root);
		root->pipe.pid = fork();
		if (root->pipe.pid == -1)
			pipe_err(root, line);
		else if (root->pipe.pid != 0)
		{
			close(root->pipe.fd[1]);
			head = head->next;
		}
		else
			break ;
	}
	return (pipe_init_helper_2(root, head, fd_info));
}

void	pipe_init_helper(t_lexer *head, t_root *root)
{
	if (root->pipe.fd_last[0] != -1)
		close(root->pipe.fd_last[0]);
	if (root->pipe.count >= 2)
		root->pipe.fd_last[0] = root->pipe.fd[0];
	if (head->next == NULL)
	{
		root->pipe.total_count = root->pipe.count;
		root->pipe.count = 0;
	}
	else
		pipe(root->pipe.fd);
}

pid_t	pipe_init_helper_2(t_root *root, t_lexer *head, t_fd_info *fd_info)
{
	if (root->pipe.pid != 0)
	{
		close(root->pipe.fd_last[0]);
		return (root->pipe.total_count);
	}
	cp_function(root->pipe.count, root->pipe.fd, root->pipe.fd_last);
	execute_cmd(root, head, root->envp, fd_info);
	return (root->pipe.pid);
}
