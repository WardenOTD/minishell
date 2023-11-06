/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:49:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/03 19:20:35 by jutong           ###   ########.fr       */
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
	if (input->token[1] && hyphen(input->token[i]))
	{
		i++;
		while (input->token[i] && hyphen(input->token[i]))
			i++;
		while (input->token[i])
		{
			printf("%s", input->token[i++]);
			if (input->token[i])
				printf(" ");
		}
	}
	else
	{
		while (input->token[i])
		{
			printf("%s", input->token[i++]);
			if (input->token[i])
				printf(" ");
		}
		printf("\n");
	}
}
