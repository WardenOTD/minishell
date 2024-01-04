/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:23:03 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:23:10 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	**turn_arr_into_str(char **arr)
{
	char	*str;
	char	*tmp;
	int		i;
	char	**arg;

	i = 1;
	str = ft_strdup(arr[0]);
	while (arr[i])
	{
		tmp = ft_strjoin(str, "\7");
		free(str);
		str = ft_strjoin(tmp, arr[i]);
		free(tmp);
		i++;
	}
	arg = ft_split(str, '\7');
	free(str);
	return (arg);
}
