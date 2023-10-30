/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:19:28 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/30 14:43:45 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexer(t_lexer *input, char *line)
{
	int		i;
	t_lexer	*temp;
	t_lexer	*tail;
	char	**arr;
	char	**arr2;

	i = 0;
	temp = NULL;
	tail = NULL;
	arr = ft_split(line, '|');
	while (arr[i])
	{
		arr2 = ft_split(arr[i], ' ');
		temp =	lexerlstnew(arr2);
		if (!input)
			input = temp;
		else
			tail->next = temp;
		tail = temp;
		free2d(arr2);
		i++;
	}
	free2d(arr);
	return (input);
}

t_lexer	*freelexer(t_lexer *input)
{
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer *tmpnxt;

	head = input;
	tmp = head->next;
	while (tmp)
	{
		tmpnxt = tmp->next;
		free2d(tmp->arg);
		free(tmp);
		tmp = tmpnxt;
	}
	free2d(head->arg);
	free(head);
	input = NULL;
	return (input);
}
