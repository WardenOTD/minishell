/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:23:15 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/18 11:38:15 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*d;

	i = 0;
	d = (char *)b;
	while (i != len)
	{
		*d = c;
		i++;
		d++;
	}
	return (b);
}
