/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:28:06 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/23 13:38:51 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy(char *s, char *ss, int start, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i == start)
		{
			while (j < len)
			{
				ss[j] = s[i + j];
				j++;
			}
			ss[j] = 0;
			return ;
		}
		i++;
	}
	return ;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ss = (char *)ft_calloc((len + 1), sizeof(char));
	if (!ss)
		return (0);
	copy((char *)s, ss, (int)start, (int)len);
	return (ss);
}
