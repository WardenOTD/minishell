/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:09:27 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/02 17:09:58 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*remove_exp(char *needle, char *haystack)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\''
					|| haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' '
					|| !haystack[i + j + 1]))
				return (remove_exp_helper(i, j, haystack, needle));
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*remove_exp_helper(int i, int j, char *haystack, char *needle)
{
	char	*ret;
	int		k;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack)
				- ft_strlen(needle) + 1));
	ret[ft_strlen(haystack) - ft_strlen(needle)] = 0;
	k = -1;
	while (++k != i)
		ret[k] = haystack[k];
	i += j;
	while (haystack[++i])
		ret[k++] = haystack[i];
	free(haystack);
	// free(needle);
	return (ret);
}

char	*add_exp(char *needle, char *haystack, char *val)
{
	int	i;
	int	j;
	int	ij[2];

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\''
					|| haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' '
					|| haystack[i + j + 1] == '$' || !haystack[i + j + 1]))
			{
				ij[0] = i;
				ij[1] = j;
				return (add_exp_helper(ij, haystack, needle, val));
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*add_exp_helper(int ij[2], char *haystack, char *needle, char *val)
{
	char	*ret;
	int		k;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack)
				- ft_strlen(needle) + ft_strlen(val) + 1));
	ret[ft_strlen(haystack) - ft_strlen(needle)
		+ ft_strlen(val)] = 0;
	k = -1;
	while (++k != ij[0])
		ret[k] = haystack[k];
	ij[0] += ij[1];
	ij[1] = 0;
	while (val[ij[1]])
		ret[k++] = val[ij[1]++];
	while (haystack[++ij[0]])
		ret[k++] = haystack[ij[0]];
	free(haystack);
	return (ret);
}
