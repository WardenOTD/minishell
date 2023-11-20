/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:49:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/20 12:59:36 by jteoh            ###   ########.fr       */
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
	// for (int i = 0; input->arg[i]; i++)
	// {
	// 	printf("%d  --  %s\n", i, input->arg[i]);
	// }
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
			printf("%s", input->arg[i]);
			if (input->arg[++i])
				printf(" ");
		}
		printf("\n");
	}
}
