/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/08 19:25:16 by jteoh            ###   ########.fr       */
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
		arr2 = split2(arr[i], ' ');
		temp = lexerlstnew(arr2);
		if (!input)
			input = temp;
		else
			tail->next = temp;
		tail = temp;
		free2d(arr2);
		i++;
	}
	free2d(arr);
	input = requote(input);
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

t_lexer	*requote(t_lexer *input)
{
	t_lexer	*head;
	t_lexer	*tail;
	// char	*tmp;

	head = input;
	while (head)
	{
		tail = head->next;
		if (quote_count(head->arg) != 0)
		{
			while (quote_count(head->arg) % 2 != 0)
			{
				head->arg = dArray_join(head->arg, tail->arg);
				tail = tail->next;
				free(head->next);
				head->next = tail;
			}
			head->arg = inArray_join(head->arg);
		}
		// else
		// {
		// 	tmp = flatten_arr(head->arg);
		// 	free2d(head->arg);
		// 	head->arg = ft_split(tmp, ' ');
		// 	// for (int i = 0; head->arg[i]; i++)
		// 	// 	dprintf(1, "%s\n", head->arg[i]);
		// }
		head = tail;
	}
	return (input);
}

int	quote_count(char **arr)
{
	int	i;
	int	j;
	int	val;

	//  Counting quotes per node,, if not multiple of 2,, means need to conjoin nodes due to split by | (pipe)
	i = 0;
	val = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '"' || arr[i][j] == '\'')
				val++;
			j++;
		}
		i++;
	}
	return (val);
}

char	**dArray_join(char **front, char **back)
{
	int		i;
	int		j;
	char	**result;

	//  Conjoining the 2 double arrays from node1 and node->next placed back into node1
	i = 0;
	j = 0;
	while (front[i])
		i++;
	while (back[j])
		j++;
	result = (char **)malloc(sizeof(char *) * (i + j + 2));
	result[i + j + 1] = 0;
	i = -1;
	j = -1;
	while (front[++i])
		result[i] = ft_strdup(front[i]);
	result[i] = ft_strdup("|");
	while (back[++j])
		result[++i] = ft_strdup(back[j]);
	free2d(front);
	free2d(back);
	return (result);
}

char	*flatten_arr(char **arr)
{
	int		i;
	char	*rearray;

	//  Turning 2d array into 1d array for easier indexing
	i = 0;
	rearray = NULL;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		if (!rearray)
			rearray = ft_strdup(arr[i]);
		else
		{
			rearray = ft_strjoin(rearray, " ");
			rearray = ft_strjoin(rearray, arr[i]);
		}
		printf("%s\n", rearray);
		i++;
	}
	printf("%s\n", rearray);
	return (rearray);
}

char	**inArray_join(char	**arr)
{
	int	i;
	int	j;
	int	flag;
	char	**result;
	char	*rearray;

	rearray = flatten_arr(arr);
	//  Counting spaces for malloc 2d array [ Basically modified split to fit the quote shenanigans ]
	j = 0;
	i = 0;
	flag = 0;
	while (rearray[j])
	{
		if (flag == 0 && (rearray[j] == ' ' && rearray[j + 1] != ' ' && rearray[j + 1] != 0))
			i++;
		if (rearray[j] == '"' || rearray[j] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		j++;
	}
	//  Malloc 2d array according to spaces counted
	result = (char **)malloc(sizeof(char *) * (i + 1));
	result[i] = 0;
	//  Malloc and convert 1d array into 2d array
	int	spacer;
	int flag2;

	spacer = 0;
	flag2 = 0;
	j = 0;
	i = 0;
	while (rearray[j])
	{
		if (rearray[j] == '"' || rearray[j] == '\'')
		{
			if (flag2 == 0)
				flag2 = 1;
			else
				flag2 = 0;
		}
		if (flag2 == 1 || rearray[j] != ' ')
			spacer++;
		if ((rearray[j] == ' ' || rearray[j + 1] == 0) && spacer > 0 && flag2 == 0)
		{
			//echo asd asd     sdki kaw "    w das | askduu asd "
			if (rearray[j + 1] == 0)
				j++;
			result[i] = ft_substr(rearray, (j - spacer), spacer);
			i++;
			spacer = 0;
			if (rearray[j] == 0)
				j--;
		}
		j++;
	}
	free(rearray);
	free(arr);
	return (result);
}
