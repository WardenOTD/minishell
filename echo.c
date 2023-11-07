/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:49:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:44:16 by jteoh            ###   ########.fr       */
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

void	echo(t_lexer *input)
{
	int	i;

	i = 1;
	if (input->arg[1] && hyphen(input->arg[i]))
	{
		i++;
		while (input->arg[i] && hyphen(input->arg[i]))
			i++;
		while (input->arg[i])
		{
			printf("%s", input->arg[i++]);
			if (input->arg[i])
				printf(" ");
		}
	}
	else
	{
		while (input->arg[i])
		{
			printf("%s", input->arg[i++]);
			if (input->arg[i])
				printf(" ");
		}
		printf("\n");
	}
}
