/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:08:14 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/09 14:34:41 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)ft_calloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1,
			sizeof(char));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while ((char)s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while ((char)s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
