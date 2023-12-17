/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/17 23:25:58 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

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
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
	t_env		*env;
	t_lexer 	*input;
	t_exp		*exp;
	t_fd_info	fd_info;
	char	*line;

	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	init(&env, &input, &exp, &fd_info);
	env = get_env(env, envp);
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit", 5))
			handle(line);
		if (ft_strlen(line))
			add_history(line);
		if (ft_strlen(line))
		{
			exp = get_exp(exp, env);
			input = lexer(input, line, env);
			execute_cmd(input, env, exp, envp, &fd_info);
			// call(input, env, exp, envp);
			input = freelexer(input);
			exp = free_exp(exp);
		}
		signal(SIGINT, ctrlc);
		free(line);
	}
}
