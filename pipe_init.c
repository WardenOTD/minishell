/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:04:19 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/20 15:14:05 by jteoh            ###   ########.fr       */
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

pid_t	pipe_init(t_root *root, char *line)
{
	int		fd[2];
	pid_t	pid;
	int		fd_last[2];
	t_lexer	*head;
	int		count;

	pid = 1;
	fd_last[0] = -1;
	fd_last[1] = -1;
	head = root->input;
	count = 0;
	while(head != NULL)
	{
		pipe(fd);
		if (fd_last[0] != -1)
			close(fd_last[0]);
		if (fd_last[1] != -1)
			close(fd_last[1]);
		fd_last[0] = fd[0];
		fd_last[1] = fd[1];
		count++;
		if (head->next == NULL)
			count = 0;
		pid = fork();
		if (pid == -1)
			pipe_err(root, line);
		if (pid != 0)
			head = head->next;
		else
			break ;
	}
	if (pid != 0)
	{
		close(fd_last[0]);
		close(fd_last[1]);
		return (pid);
	}
	cp_function(count, fd);
	return (pid);
}

void	cp_function(int count, int fd[2])
{
	if (count == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (count == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}
