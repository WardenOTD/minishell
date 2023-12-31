/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:09:27 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 15:12:54 by jteoh            ###   ########.fr       */
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
					|| haystack[i + j + 1] == '"'
					|| haystack[i + j + 1] == ' '
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
					|| haystack[i + j + 1] == '"'
					|| haystack[i + j + 1] == ' '
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

char	*replace_expand_helper(char *str, char *to_r,
	char *new_value, char *ret)
{
	int		i;
	int		j;
	int		k;
	int		once;

	i = 0;
	j = 0;
	k = 0;
	once = 0;
	while (str[i])
	{
		if (yes_expand(str[i], str[i + 1]) && !once)
		{
			if (new_value)
				while (new_value[k])
					ret[j++] = new_value[k++];
			i += ft_strlen(to_r);
			once = 1;
		}
		else
			ret[j++] = str[i++];
	}
	return (ret);
}
