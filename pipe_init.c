/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:04:19 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/20 18:37:04 by jteoh            ###   ########.fr       */
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

pid_t	pipe_init(t_root *root, char *line, char **envp, t_fd_info *fd_info)
{
	int		fd[2];
	pid_t	pid;
	int		fd_last[2];
	t_lexer	*head;
	int		count;
	int		total_count;

	pid = 1;
	fd_last[0] = -1;
	fd_last[1] = -1;
	head = root->input;
	count = 0;
	while (head != NULL)
	{
		count++;

		if (fd_last[0] != -1)
			close(fd_last[0]);

		if (count >= 2)
		{
			fd_last[0] = fd[0];
		}
		if (head->next == NULL)
		{
			total_count = count;
			count = 0;
		}
		else
		{
			pipe(fd);
		}
		pid = fork();
		if (pid == -1)
		{
			pipe_err(root, line);
		}
		else if (pid != 0)
		{
			close(fd[1]);
			head = head->next;
		}
		else
		{
			break;
		}
	}
	if (pid != 0)
	{
		close(fd_last[0]);
		return (total_count);
	}
	cp_function(count, fd, fd_last);
	execute_cmd(root, head, envp, fd_info);
	return (pid);
}

void	cp_function(int count, int fd[2], int prev_fd[2])
{
	if (count == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (count == 0)
	{
		dup2(prev_fd[0], STDIN_FILENO);
	}
	else
	{
		close(fd[0]);
		dup2(prev_fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(prev_fd[0]);
	}
}
