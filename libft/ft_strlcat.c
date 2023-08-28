/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:36:14 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/18 11:43:58 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	j;

	dlen = ft_strlen(dst);
	slen = ft_strlen((char *)src);
	i = 0;
	j = dlen;
	if (dlen >= dstsize)
	{
		return (slen + dstsize);
	}
	if (dlen < dstsize - 1 && dstsize > 0)
	{
		while (src[i] && dlen + i < dstsize - 1)
		{
			dst[j] = src[i];
			j++;
			i++;
		}
		dst[j] = '\0';
	}
	return (dlen + slen);
}
