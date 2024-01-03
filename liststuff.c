/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liststuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:31:18 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/03 17:22:33 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexerlstnew(char **arr)
{
	t_lexer	*head;
	int		i;

	i = 0;
	head = (t_lexer *)malloc(sizeof(t_lexer));
	if (!head)
		return (0);
	while (arr[i])
		i++;
	head->arg = (char **)malloc(sizeof(char *) * (i + 1));
	head->arg[i] = NULL;
	i = 0;
	while (arr[i])
	{
		head->arg[i] = ft_strdup(arr[i]);
		i++;
	}
	head->next = NULL;
	return (head);
}

t_env	*envlstnew(char *k, char *v)
{
	t_env	*head;

	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (0);
	head->key = ft_strdup(k);
	if (!v)
		head->value = NULL;
	else
		head->value = ft_strdup(v);
	head->next = NULL;
	return (head);
}

t_exp	*explstnew(char *k, char *v)
{
	int		j;
	t_exp	*head;

	if (v)
	{
		j = ft_strlen(k) + ft_strlen(v) + 1;
		if (v[0] != '"')
			j += 2;
		else if (v[0] == 0)
			j += 2;
	}
	if (!v)
		j = ft_strlen(k);
	head = (t_exp *)malloc(sizeof(t_exp));
	if (!head)
		return (0);
	if (v)
		head->export = (char *)malloc(sizeof(char) * (j + 1));
	else if (!v)
		head->export = (char *)malloc(sizeof(char) * (j + 1));
	if (!head->export)
		return (0);
	head->export[j] = 0;
	return (explstnew_helper(head, k, v));
}

t_exp	*explstnew_helper(t_exp *head, char *k, char *v)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (v)
	{
		while (k[++i])
			head->export[i] = k[i];
		head->export[i++] = '=';
		if (v[0] == 0)
			return (explstnew_helper_helper(head, i));
		if (v[0] == '"')
			j++;
		head->export[i] = '"';
		while (v[++j])
			head->export[++i] = v[j];
		if (v[--j] != '"')
			head->export[++i] = '"';
	}
	else if (!v)
	{
		while (k[++i])
			head->export[i] = k[i];
	}
	head->next = NULL;
	return (head);
}

t_exp	*explstnew_helper_helper(t_exp *head, int i)
{
	head->export[i++] = '"';
	head->export[i] = '"';
	head->next = NULL;
	return (head);
}
