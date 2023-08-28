/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:15:04 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/23 13:06:59 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(size_t count, size_t size)
{
	if (count == 0 || size == 0)
		return (1);
	if (count > __INT_MAX__ || size > __INT_MAX__)
		return (0);
	if (count >= __INT_MAX__ / size || size >= __INT_MAX__ / count)
		return (0);
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*arr;

	if (check(count, size) == 0)
		return (0);
	arr = (void *)malloc(count * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, count * size);
	return ((void *)arr);
}
