/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:04 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/05 17:56:38 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	lexer(t_root *root, char *line)
{
	lexer_helper(root, line);
	root->input = expand(root->input, root->env);
	root->input->arg = remove_quotes(root->input->arg);
	if (root->input->next != NULL)
		return (1);
	return (0);
}

void	lexer_helper(t_root *root, char *line)
{
	int		i;
	t_lexer	*temp;
	t_lexer	*tail;
	char	**arr2;
	char	***tri_pp_arr;

	i = 0;
	temp = NULL;
	tail = NULL;
	arr2 = splitter(line);
	tri_pp_arr = arr_arr_split(arr2);
	while (tri_pp_arr[i])
	{
		temp = lexerlstnew(tri_pp_arr[i]);
		if (!root->input)
			root->input = temp;
		else
			tail->next = temp;
		tail = temp;
		free2d(tri_pp_arr[i]);
		i++;
	}
	free2d(arr2);
	free(tri_pp_arr);
}

t_lexer	*freelexer(t_lexer *input)
{
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer	*tmpnxt;

	if (!input)
		return (NULL);
	head = input;
	tmp = head->next;
	while (tmp)
	{
		tmpnxt = tmp->next;
		if (tmp->arg)
			free2d(tmp->arg);
		free(tmp);
		tmp = tmpnxt;
	}
	if (head->arg)
		free2d(head->arg);
	free(head);
	input = NULL;
	return (input);
}
