/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/27 17:20:06 by jteoh            ###   ########.fr       */
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
	while (line[++i] != 0)
		free(line[i]);
	free (line);
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

void	init(t_env **env, t_lexer **input)
{
	(*env) = NULL;
	(*input) = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_lexer *input;
	char	*line;

	signal(SIGINT, ctrlc);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	init(&env, &input);
	env = get_env(env, envp);
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit", 5))
			handle(line);
		if (ft_strlen(line))
			add_history(line);
		if (!ft_strncmp(line, "env", 4))
			display_env(env);
		else if (ft_strlen(line))
		{
			input = lexer(input, line);
			freelexer(input);
		}
		free(line);
	}
}
