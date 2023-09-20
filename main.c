/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:11:13 by jteoh             #+#    #+#             */
/*   Updated: 2023/09/20 13:39:40 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	handle(char *line)
{
	printf("exit\n");
	free(line);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char	*line;
	while (1)
	{
		line = readline("Minishell$ ");
		if (line == NULL || !ft_strncmp(line, "exit", 5))
			handle(line);
		if (ft_strlen(line))
			add_history(line);
		if (!ft_strncmp(line, "env", 4))
			display_env(envp);
		free(line);
	}
}
