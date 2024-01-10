/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/10 17:46:21 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

//int	g_status_code;

void	free2d(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

void	main_helper_1(char *line, t_root *root, t_fd_info *fd_info)
{
	if (line == NULL || !ft_strncmp(line, "exit", 5))
		handle(line, root->env, fd_info);
	if (ft_strlen(line))
		add_history(line);
	if (find_unclosed_quote(line))
		printf("Unclosed quote detected\n");
	else if (invalid_pipe_front(line) || invalid_pipe_back(line) || invalid_redir_mod(line))
		printf("minishell: syntax error near unexpected token '|'\n");
	else if (invalid_redir(line))
		printf("minishell: syntax error near unexpected token `newline'\n");
	else if (ft_strlen(line))
		main_helper_2(root, fd_info, line);
}

void	main_helper_2(t_root *root, t_fd_info *fd_info, char *line)
{
	pid_t	pid;

	root->exp = get_exp(root->exp, root->env);
	if (lexer(root, line, 0) == 1)
	{
		root->has_pipe = 1;
		pid = pipe_init(root, line, fd_info);
		if (pid == 0)
			exit (0);
		else
			main_helper_3(pid);
	}
	else
		execute_cmd(root, root->input, root->envp, fd_info);
	root->input = freelexer(root->input);
	root->exp = free_exp(root->exp);
}

void	main_helper_3(pid_t pid)
{
	int	err;

	err = 0;
	while (pid)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &err, 0);
		pid--;
	}
	if (WIFSIGNALED(err))
	{
		write(0, "\n", 1);
		g_status_code = ((WTERMSIG(err) + 128) % 256);
	}
	else
		g_status_code = (WEXITSTATUS(err) % 256);
}

int	main(int argc, char **argv, char **envp)
{
	t_root		root;
	t_fd_info	fd_info;

	g_status_code = 0;
	(void)argc;
	(void)argv;
	init_2(&root, &fd_info, envp);
	while (1)
	{
		root.has_pipe = 0;
		root.line = readline("Minishell$ ");
		main_helper_1(root.line, &root, &fd_info);
		handle_ctrlc(&fd_info);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrlc);
		if (root.line)
			free(root.line);
	}
	return (0);
}
