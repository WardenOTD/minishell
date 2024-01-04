/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:24:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:24:20 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	***arr_arr_split(char **arr)
{
	int		i;
	int		j;
	int		pp_i;
	char	***ret;

	i = 0;
	j = 0;
	pp_i = 0;
	ret = (char ***) malloc (sizeof(char **) * 20);
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "|", 2))
		{
			ret[pp_i] = arr_dup_n(arr, j, i);
			i++;
			j = i;
			pp_i++;
		}
		i++;
	}
	ret[pp_i] = arr_dup_n(arr, j, i);
	pp_i++;
	ret[pp_i] = 0;
	return (ret);
}
