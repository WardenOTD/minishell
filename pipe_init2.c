/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:26:41 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 14:36:13 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	cp_function(int count, int fd[2], int prev_fd[2])
{
	if (count == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (count == 0)
		dup2(prev_fd[0], STDIN_FILENO);
	else
	{
		close(fd[0]);
		dup2(prev_fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(prev_fd[0]);
	}
}

int	invalid_pipe_front(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (str[i] != '|' && str[i] != '\'' && str[i] != '\"')
				break ;
			else if (str[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	invalid_pipe_back(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (str[i] != ' ')
		{
			if (str[i] != '|')
				break ;
			else if (str[i] == '|')
				return (1);
		}
		i--;
	}
	return (0);
}
