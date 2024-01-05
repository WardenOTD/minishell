/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:16:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/05 18:13:36 by jteoh            ###   ########.fr       */
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
		ret[k++] = str[j++];
	ret[k] = 0;
	return (ret);
}

char	*get_str_inquote(char *str, int info, int *pos)
{
	int		i;
	int		j;
	char	*ret;
	int		in_quote;

	i = *pos + 1;
	j = i;
	in_quote = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quote++;
		if ((is_token(str[i]) && in_quote % 2 == 0)
			|| (str[i] == ' ' && in_quote % 2 == 0)
			|| (str[i] == info && in_quote % 2 == 1
				&& (!str[i + 1] || str[i] == ' ')))
			break ;
		i++;
	}
	ret = create_str(str, i, j - 1, (i - *pos + 1 + in_quote + 1));
	*pos = i;
	return (ret);
}

char	*get_str_outquote(char *str, int *pos)
{
	int		i;
	int		j;
	char	*ret;
	int		in_quote;

	i = *pos;
	j = i;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quote++;
		if ((is_token(str[i]) && in_quote % 2 == 0)
			|| (str[i] == ' ' && in_quote % 2 == 0))
			break ;
		i++;
	}
	ret = create_str(str, i, j, (i - *pos + 1 + in_quote));
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
	ret = (char **) malloc (sizeof(char *) * 30);
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
