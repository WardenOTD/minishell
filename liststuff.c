/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liststuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:31:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/17 13:52:35 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexerlstnew(t_lexer *head)
{
	if (head->next != 0)
		return (lexerlstnew(head->next));
	else
	{
		head->next = (t_lexer *)malloc(sizeof(t_lexer));
		head->next->next = NULL;
	}
	return (head->next);
}

t_env	*envlstnew(t_env *head)
{
	printf("in list new\n");
	if (head->next)
	{
		printf("enter if state\n");
		return (envlstnew(head->next));

	}
	else
	{
		printf("enter else state\n");
		head->next = (t_env *)malloc(sizeof(t_env));
		head->next->next = NULL;
		printf("complete else state\n");
	}
	return (head->next);
}

t_lexer	*lexerlstappend(t_lexer *head, char **arr)
{
	if (!head->arg)
		head->arg = arr;
	else
		return (lexerlstappend(head->next, arr));
	return (head);
}

t_env	*envlstappend(t_env *head, char *k, char *v)
{
	printf("append\n");
	if (!head->key)
	{
		head->key = k;
		head->value = v;
	}
	else
		return (envlstappend(head->next, k, v));
	return (head);
}
