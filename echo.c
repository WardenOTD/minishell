/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:49:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/09/22 15:02:50 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	hyphen(char *hy)
{
	int	i;

	i = 0;
	if (hy[i] == '-')
		return (n(hy));
	return (0);
}

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
	if (input->line[1] && hyphen(input->line[i]))
	{
		i++;
		while (input->line[i] && hyphen(input->line[i]))
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
