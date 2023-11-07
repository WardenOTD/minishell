/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:19 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:58:22 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	return (0);
}
