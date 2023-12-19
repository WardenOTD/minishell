/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:04:19 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/19 17:41:44 by jteoh            ###   ########.fr       */
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

void	pipe_init(t_root *root, char *line)
{
	int		fd[2];
	pid_t	pid;
	int		fd_last;
	t_lexer	*head;
	int		count;

	pid = 1;
	fd_last = -1;
	head = root->input;
	count = 0;
	while(head != NULL)
	{
		pipe(fd);
		if (fd_last != -1)
			close(fd_last);
		fd_last = fd[0];
		count++;
		if (head->next == NULL)
			count = 0;
		pid = fork();
		if (pid == -1)
			pipe_err(root, line);
		if (pid != 0)
			close(fd[1]);
		head = head->next;
	}
	if (pid != 0)
		close(fd_last);
	//child process function
}

/* child process function(count){
	if count == 1{
		close fd[0];
		dup2(fd[1], stdout_fileno);
		close fd[1];
	}
	elif count == 0{
		close fd[1];
		dup2(fd[0], stdin_fileno);
		close fd[0];
	}
	else
		dup2(fd[0], stdin_fileno)
		dup2(fd[1], stdout_fileno)
		close fd[0];
		close fd[1];
}
*/
