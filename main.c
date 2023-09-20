/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2023/09/20 17:23:05 by jteoh            ###   ########.fr       */
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

	i = 0;
	while (line[i] != 0)
		free(line[i++]);
	free (line);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	env;
	t_input	input;
	env.envp = envp;

	char	*line;

	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit", 5))
			handle(line);
		if (ft_strlen(line))
			add_history(line);
		if (!ft_strncmp(line, "env", 4))
			display_env(&env);
		else if (ft_strlen(line))
		{
			input.line = ft_split(line, ' ');
			if (input.line && input.line[0] )
				call(&input);
			// for (int i = 0; input.line[i]; i++)
			// 	printf("%s\n", input.line[i]);
			free2d(input.line);
		}
		free(line);
	}
}
