/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:01:36 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 12:22:07 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	env_darr(t_root *root)
{
	t_env	*head;
	int		i;

	head = root->env;
	i = envlist_len(head);
	root->envp = (char **)malloc(sizeof(char *) * (i + 1));
	root->envp[i] = NULL;
	i = 0;
	while (head)
	{
		root->envp[i++] = env_arr(head);
		head = head->next;
	}
}

char	*env_arr(t_env *head)
{
	int		i;
	int		j;
	char	*arr;

	i = 0;
	j = 0;
	i = ft_strlen(head->key);
	if (head->value)
		i += ft_strlen(head->value);
	i += 1;
	arr = (char *)malloc(sizeof(char) * (i + 1));
	arr[i] = 0;
	i = 0;
	while (head->key[i])
	{
		arr[i] = head->key[i];
		i++;
	}
	arr[i++] = '=';
	if (head->value)
		while (head->value[j])
			arr[i++] = head->value[j++];
	return (arr);
}

int	envlist_len(t_env *env)
{
	t_env	*head;
	int		i;

	head = env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}
