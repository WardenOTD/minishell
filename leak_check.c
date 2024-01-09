/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:04:17 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 16:05:43 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	printf("===================================\n");
	while (1)
	{
		system("leaks -q minishell");
		printf("===================================\n");
		sleep(5);
	}
}

/*-------Script For Running Leak Check-------*/