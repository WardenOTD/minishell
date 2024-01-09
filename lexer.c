/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:04 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 10:30:43 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	lexer(t_root *root, char *line)
{
	char	*str;

	str = ft_strdup(line);
	str = expand_helper_1(str, root->env, 0);
	lexer_helper(root, str);
	// root->input = expand(root->input, root->env);
	root->input->arg = remove_quotes(root->input->arg);
	free(str);
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
