/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:25:02 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/10 15:38:11 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	display_exp(t_exp *exp)
{
	char	*tmp;
	t_exp	*head;

	head = exp;
	while (head->next)
	{
		if (bubble_sort(head->export, head->next->export) > 0)
		{
			tmp = head->next->export;
			head->next->export = head->export;
			head->export = tmp;
		}
		head = head->next;
	}
	if (!sort_check(exp))
	{
		display_exp(exp);
		return ;
	}
	head = exp;
	while (head)
	{
		printf("declare -x %s\n", head->export);
		head = head->next;
	}
}

int	sort_check(t_exp *exp)
{
	t_exp	*head;

	head = exp;
	while (head->next)
	{
		if (bubble_sort(head->export, head->next->export) > 0)
			return (0);
		head = head->next;
	}
	return (1);
}

int	bubble_sort(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

t_exp	*get_exp(t_exp *exp, t_env *env)
{
	t_env	*temp;
	t_exp	*tmp;
	t_exp	*tail;

	temp = env;
	tail = NULL;
	while (temp)
	{
		tmp = explstnew(temp->key, temp->value);
		if (!exp)
			exp = tmp;
		else
			tail->next = tmp;
		tail = tmp;
		temp = temp->next;
	}
	return (exp);
}

t_exp	*free_exp(t_exp *exp)
{
	t_exp	*head;
	t_exp	*tmp;
	t_exp	*tmpnxt;

	head = exp;
	tmp = head->next;
	while (tmp)
	{
		tmpnxt = tmp->next;
		if (tmp->export)
			free(tmp->export);
		free(tmp);
		tmp = tmpnxt;
	}
	if (head->export)
		free(head->export);
	free(head);
	exp = NULL;
	return (exp);
}
