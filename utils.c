/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:36:45 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 13:41:40 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	get_arraysize(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**arr_dup_n(char **arr, int start, int end)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **) malloc (sizeof(char *) * (end - start + 2));
	while (start < end)
	{
		ret[i] = ft_strdup(arr[start]);
		i++;
		start++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_strjoin_free(char *s1, char *s2)
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
	free(s1);
	return (s3);
}

void	error_msg(char *wrongcmd, char *msg)
{
	if (wrongcmd)
	{
		write (STDERR_FILENO, wrongcmd, ft_strlen(wrongcmd));
		write (STDERR_FILENO, ": ", 2);
	}
	write (STDERR_FILENO, msg, ft_strlen(msg));
	write (STDERR_FILENO, "\n", 1);
}
