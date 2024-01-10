/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:53:55 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/10 15:53:14 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*remove_quote_helper_2(char type, int in_quote, char *str, char *ret)
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

int	get_nor_arr_size(char *str)
{
	int		ret;
	int		i;
	int		in_quote;
	char	type;

	ret = 0;
	i = 0;
	in_quote = 0;
	type = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (in_quote % 2 == 0)
				type = str[i];
			if (str[i] == type)
				in_quote++;
		}
		if ((str[i] == '|' || str[i] == '>' || str[i] == '<'
				|| str[i] == ' ') && in_quote % 2 == 0)
			ret += 2;
		i++;
	}
	ret++;
	return (ret);
}

int	get_tri_arr_size(char **arr)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], "|", 2))
			ret++;
		i++;
	}
	ret++;
	return (ret);
}
