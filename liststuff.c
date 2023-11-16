/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liststuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:31:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/14 10:48:24 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexerlstnew(char **arr)
{
	t_lexer *head;
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
	head->value = ft_strdup(v);
	head->next = NULL;
	return (head);
}

t_exp	*explstnew(char *k, char *v)
{
	int		i;
	int		j;
	t_exp	*head;

	i = -1;
	if (v)
		j = ft_strlen(k) + ft_strlen(v) + 2;
	else if (!v)
		j = ft_strlen(k) + 1;
	head = (t_exp *)malloc(sizeof(t_exp));
	if (!head)
		return (0);
	head->export = (char *)malloc(sizeof(char) * j);
	if (!head->export)
		return (0);
	head->export[--j] = 0;
	j = -1;
	if (v)
	{
		while (k[++i])
			head->export[i] = k[i];
		head->export[i] = '=';
		while (v[++j])
			head->export[++i] = v[j];
	}
	else if (!v)
	{
		while (k[++i])
			head->export[i] = k[i];
	}
	head->next = NULL;
	return (head);
}
