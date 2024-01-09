/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:16:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 12:22:03 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*create_str(char *str, int i, int j, int size)
{
	int		k;
	char	*ret;

	k = 0;
	ret = malloc (sizeof(char) * size);
	while (j < i)
	{
		ret[k++] = str[j++];
	}
	ret[k] = 0;
	return (ret);
}

char	*get_str_inquote(char *str, int info, int *pos)
{
	int		i;
	int		j;
	char	*ret;
	int		flag[4];

	i = *pos;
	j = i;
	set_arr_to_zero(flag, 4);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			get_flag(flag, str[i], i);
		if ((is_token(str[i]) && analyze_flag_2(flag) == 1)
			|| (str[i] == ' ' && analyze_flag_2(flag) == 1)
			|| (str[i] == info
				&& (!str[i + 1] || str[i + 1] == ' ')))
		{
			i++;
			break ;
		}
		i++;
	}
	ret = create_str(str, i, j, (i - *pos + 1 + flag[0] + flag[2] + 1));
	*pos = i;
	return (ret);
}

char	*get_str_outquote(char *str, int *pos)
{
	int		i;
	int		j;
	char	*ret;
	int		flag[4];

	i = *pos;
	j = i;
	set_arr_to_zero(flag, 4);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			get_flag(flag, str[i], i);
		if ((is_token(str[i]) && analyze_flag_2(flag) == 1)
			|| (str[i] == ' ' && analyze_flag_2(flag) == 1))
			break ;
		i++;
	}
	ret = create_str(str, i, j, (i - *pos + 1 + flag[0] + flag[2]));
	*pos = i;
	return (ret);
}

char	*get_str_token(char *str, int *pos)
{
	int		i;
	char	*ret;

	i = *pos;
	ret = NULL;
	if (str[i] == '|')
		ret = ft_strdup("|");
	else if (str[i] == '<' && str[i + 1] == '<')
		ret = ft_strdup("<<");
	else if (str[i] == '<' && str[i + 1] != '<')
		ret = ft_strdup("<");
	else if (str[i] == '>' && str[i + 1] == '>')
		ret = ft_strdup(">>");
	else if (str[i] == '>' && str[i + 1] != '>')
		ret = ft_strdup(">");
	*pos += ft_strlen(ret);
	return (ret);
}

char	**splitter(char *str)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = (char **) malloc (sizeof(char *) * (get_nor_arr_size(str) + 1));
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			ret[j++] = get_str_token(str, &i);
		else if (str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
			ret[j++] = get_str_outquote(str, &i);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			ret[j++] = get_str_inquote(str, str[i], &i);
			if (str[i] == '\"' || str[i] == '\'')
				i++;
		}
		else
			i++;
	}
	ret[j] = 0;
	return (ret);
}
