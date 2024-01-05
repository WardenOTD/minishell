/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:24:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/05 18:03:42 by jutong           ###   ########.fr       */
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

int		is_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int		get_new_len(char *str)
{
	int		i;
	int		j;
	int		type;
	int		in_quote;

	i = 0;
	j = 0;
	type = 0;
	in_quote = 0;
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
				j++;
		}
		else if (str[i] != '\"' || str[i] != '\'')
			j++;
		i++;
	}
	i += 1;
	return (i);
}

char	*remove_quote_helper(char *str)
{
	int		i;
	int		j;
	int		type;
	int		in_quote;
	char	*ret;

	i = 0;
	j = 0;
	type = 0;
	in_quote = 0;
	ret = malloc (sizeof(char) * get_new_len(str));
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
	ret[j] = 0;
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
