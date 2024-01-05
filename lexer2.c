/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:16:08 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/05 14:28:29 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int		is_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*get_str_inquote(char *str, int info, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	int		in_quote;

	i = *pos;
	j = i;
	k = 0;
	in_quote = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quote++;
		if ((is_token(str[i]) && in_quote % 2 == 0) || (str[i] == ' ' && in_quote % 2 == 0)
				|| (str[i] == info && in_quote == 1 && (!str[i + 1] || str[i] == ' ')))
			break ;
		i++;
	}
	ret = malloc (sizeof(char) * (i - *pos + 1 - in_quote + 1));
	while (j < i)
	{
		if (str[j] == '\'' || str[j] == '\"')
			j++;
		else
			ret[k++] = str[j++];
	}
	ret[k] = 0;
	*pos = i;
	return (ret);
}

char	*get_str_outquote(char *str, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	int		in_quote;

	i = *pos;
	j = i;
	k = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quote++;
		if ((is_token(str[i]) && in_quote % 2 == 0) || (str[i] == ' ' && in_quote % 2 == 0))
			break ;
		i++;
	}
	ret = malloc (sizeof(char) * (i - *pos + 1 - in_quote));
	while (j < i)
	{
		if (str[j] == '\'' || str[j] == '\"')
			j++;
		else
			ret[k++] = str[j++];
	}
	ret[k] = 0;
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
			i++;
			ret[j++] = get_str_inquote(str, str[i - 1], &i);
			if (str[i] == '\"' || str[i] == '\'')
				i++;
		}
		else
			i++;
	}
	ret[j] = 0;
	return (ret);
}

int	find_unclosed_quote(char *str)
{
	int		i;
	int		pendulum;
	char	type;

	i = 0;
	type = 0;
	pendulum = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && pendulum == 0)
		{
			type = str[i];
			pendulum = 1;
		}
		else if ((str[i] == '\"' || str[i] == '\'') && pendulum > 0)
			if (str[i] == type)
				pendulum = 0;
		i++;
	}
	return (pendulum);
}
