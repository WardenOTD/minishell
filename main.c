/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/26 12:02:37 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int		g_status_code;

void	handle(char *line)
{
	printf("exit\n");
	free(line);
	exit (0);
}

void	free2d(char **line)
{
	int	i;

	i = -1;
	// for (int i = 0; line[i]; i++)
	// 	dprintf(1, "%s\n", line[i]);
	while (line[++i])
		free(line[i]);
	free(line);
}

void	ctrlc(int sig)
{
	signal(sig, SIG_IGN);
	rl_replace_line("", 0);
	write(0, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, ctrlc);
}

// void	init(t_data *data)
// {
// 	data->env = NULL;
// 	data->input = NULL;
// 	data->exp = NULL;
// 	data->in_fd = dup(STDIN_FILENO);
// 	data->out_fd = dup(STDOUT_FILENO);
// }

void	init(t_env **env, t_lexer **input, t_exp **exp, t_fd_info *fd_info)
{
	(*env) = NULL;
	(*input) = NULL;
	(*exp) = NULL;
	fd_info->in_fd = 0;
	fd_info->out_fd = 1;
	fd_info->saved_in_fd = dup(STDIN_FILENO);
	fd_info->saved_out_fd = dup(STDOUT_FILENO);

	tcgetattr(STDOUT_FILENO, &fd_info->term_attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_root		root;
	t_fd_info	fd_info;
	char		*line;
	pid_t		pid;
	int			err;

	g_status_code = 0;
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	init(&root.env, &root.input, &root.exp, &fd_info);
	root.env = get_env(root.env, envp);
	err = 0;
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit", 5))
			handle(line);
		if (ft_strlen(line))
			add_history(line);
		if (find_unclosed_quote(line))
			printf("Unclosed quote detected\n");
		else if (ft_strlen(line))
		{
			root.exp = get_exp(root.exp, root.env);
			// if (WIFSIGNALED(status)){
				// printf("signal");
				// root.input = lexer(root.input, line, root.env, (const int)WTERMSIG(status));
			// }
			// else
				root.input = lexer(root.input, line, root.env);
			pid = pipe_init(&root, line, envp, &fd_info);
			if (pid == 0)
			{
				// execute_cmd(&root, envp, &fd_info);
				exit (0);
			}
			// call(input, env, exp, envp);
			else
			{
				while (pid)
				{
					signal(SIGINT, SIG_IGN);
					waitpid(-1, &err, 0);
					pid--;
				}
				if (WIFSIGNALED(err))
				{
					write(0, "\n", 1);
					g_status_code = (WTERMSIG(err) + 128);
				}
				else
					g_status_code = WEXITSTATUS(err);
			}
			root.input = freelexer(root.input);
			root.exp = free_exp(root.exp);
		}
		signal(SIGINT, ctrlc);
		free(line);
		// if (pid == 0)
		// 	exit(0);
	}
}
