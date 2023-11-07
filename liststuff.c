/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liststuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:31:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:44:19 by jteoh            ###   ########.fr       */
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
	if (!ft_strncmp(k, "HOME", 5))
		head->value = getcwd(NULL, 0);
	else
		head->value = ft_strdup(v);
	head->next = NULL;
	return (head);
}
