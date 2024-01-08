/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:24:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 20:42:30 by jutong           ###   ########.fr       */
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
	ret = (char ***) malloc (sizeof(char **) * (get_tri_arr_size(arr) + 1));
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

int	is_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	get_new_len(char *str)
{
	int	i;
	int	j;
	int	type;
	int	in_quote;

	i = 0;
	j = 0;
	type = 0;
	in_quote = 0;
	while (str[i])
	{
		j += get_new_len_helper(&type, &in_quote, str, &i);
		i++;
	}
	j += 1;
	return (j);
}

int	get_new_len_helper(int *type, int *in_quote, char *str, int *i)
{
	int	j;

	j = 0;
	if ((str[*i] == '\"' || str[*i] == '\'') && *in_quote == 0)
	{
		*type = str[*i];
		*in_quote = 1;
	}
	else if ((str[*i] == '\"' || str[*i] == '\'') && *in_quote > 0)
	{
		if (str[*i] == *type)
			*in_quote = 0;
		else
			j++;
	}
	else if (str[*i] != '\"' || str[*i] != '\'')
		j++;
	return (j);
}

char	*remove_quote_helper(char *str)
{
	char		*ret;

	ret = malloc (sizeof(char) * get_new_len(str));
	ret[get_new_len(str) - 1] = 0;
	ret = remove_quote_helper_2(0, 0, str, ret);
	return (ret);
}
