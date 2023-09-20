/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:49:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/09/20 17:38:40 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	n(char *n)
{
	int	i;

	i = 1;
	while (n[i])
	{
		if (n[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_input *input)
{
	int	i;

	i = 1;
	if (!ft_strncmp(input->line[1], "-n", 2) && n(input->line[1]))
	{
		i++;
		while (input->line[i])
		{
			printf("%s", input->line[i++]);
			if (input->line[i])
				printf(" ");
		}
	}
	else
	{
		while (input->line[i])
		{
			printf("%s", input->line[i++]);
			if (input->line[i])
				printf(" ");
		}
		printf("\n");
	}
}
