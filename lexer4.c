/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:53:55 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/05 18:54:35 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*remove_quote_helper_2(int type, int in_quote, char *str, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && in_quote == 0)
		{
			type = str[i];
			in_quote = 1;
		}
		else if ((str[i] == '\"' || str[i] == '\'') && in_quote > 0)
		{
			if (str[i] == type)
				in_quote = 0;
			else
				ret[j++] = str[i];
		}
		else if (str[i] != '\"' || str[i] != '\'')
			ret[j++] = str[i];
		i++;
	}
	return (ret);
}

char	**remove_quotes(char **arr)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = (char **) malloc (sizeof(char *) * (get_arraysize(arr) + 1));
	while (arr[i])
	{
		ret[j] = remove_quote_helper(arr[i]);
		i++;
		j++;
	}
	ret[i] = 0;
	free2d(arr);
	return (ret);
}
