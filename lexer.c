/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:04 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/24 19:53:28 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexer(t_lexer *input, char *line, t_env *env)
{
	char	*str;
	int		i;
	char	**arr2;
	char	***tri_pp_arr;
	t_lexer	*temp;
	t_lexer	*tail;

	i = 0;
	temp = NULL;
	tail = NULL;
	str = ft_strdup(line);
	str = transform_str(str);
	arr2 = ft_split(str, 7);
	arr2 = recreate_arr(arr2);
	tri_pp_arr = arr_arr_split(arr2);
	while (tri_pp_arr[i])
	{
		// printf("test: %s\n", tri_pp_arr[i][0]);
		temp = lexerlstnew(tri_pp_arr[i]);
		if (!input)
			input = temp;
		else
			tail->next = temp;
		tail = temp;
		free2d(tri_pp_arr[i]);
		i++;
	}
	free2d(arr2);
	free(tri_pp_arr);
	free(str);
	input = expand(input, env);
	return (input);
}

t_lexer	*freelexer(t_lexer *input)
{
	t_lexer	*head;
	t_lexer	*tmp;
	t_lexer *tmpnxt;

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
	// if (head->tokens)
	// 	free2d(head->tokens);
	free(head);
	input = NULL;
	return (input);
}

// not used ---------------------------------------------------------------------------------------------------------

t_lexer	*requote(t_lexer *input)
{
	t_lexer	*head;
	t_lexer	*tail;
	char	*tmp;

	head = input;
	tmp = NULL;
	while (head)
	{
		tail = head->next;
		if (quote_count(head->arg) != 0)
		{
			while (quote_count(head->arg) % 2 != 0)
			{
				if (head->next == NULL)
				{
					printf("Syntax Error: Unclosed Quote\n");
					freelexer(input);
					return (NULL);
				}
				head->arg = dArray_join(head->arg, tail->arg);
				tail = tail->next;
				free(head->next);
				head->next = tail;
			}
			head->arg = inArray_join(head->arg);
		}
		else
		{
			tmp = flatten_arr(head->arg);
			head->arg = ft_split(tmp, ' ');
			free(tmp);
		}
		head = tail;
	}
	//---debug printing
	// if (input)
	// {
	// 	for (int i = 0; input->arg[i]; i++)
	// 	{
	// 		printf("%d -- ", i);
	// 		for (int j = 0; input->arg[i][j]; j++)
	// 		{
	// 			printf("%d ", input->arg[i][j]);
	// 		}
	// 		printf("\n%s\n", input->arg[i]);
	// 	}
	// }
	//---
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
	result[i + j + 1] = NULL;
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
	char	*tmp;

	//  Turning 2d array into 1d array for easier indexing
	i = 0;
	rearray = NULL;
	tmp = NULL;
	while (arr[i])
	{
		// printf("%s\n", arr[i]);
		if (!rearray)
			rearray = ft_strdup(arr[i]);
		else
		{
			tmp = ft_strjoin(rearray, arr[i]);
			free(rearray);
			rearray = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	free2d(arr);
	return (rearray);
}

char	*flatten_arr_w_space(char **arr)
{
	int		i;
	char	*rearray;
	char	*tmp;

	//  Turning 2d array into 1d array for easier indexing
	i = 0;
	rearray = NULL;
	tmp = NULL;
	while (arr[i])
	{
		// printf("%s\n", arr[i]);
		if (!rearray)
			rearray = ft_strdup(arr[i]);
		else
		{
			tmp = ft_strjoin(rearray, " ");
			free(rearray);
			rearray = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(rearray, arr[i]);
			free(rearray);
			rearray = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	free2d(arr);
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
	i = 1;
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
	result[i] = NULL;
	// printf("2d array size -- %d\n", i);
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
	// free2d(arr);
	return (result);
}


t_lexer	*remove_quote(t_lexer *input)
{
	t_lexer	*head;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	head = input;
	tmp = NULL;
	while (head)
	{
		i = 0;
		while (head->arg[i])
		{
			j = 0;
			while (head->arg[i][j])
			{
				if (head->arg[i][j] == '"')
				{
					j = 0;
					k = 0;
					tmp = (char *)malloc(sizeof(char) * (ft_strlen(head->arg[i]) - 2));
					tmp[ft_strlen(head->arg[i] - 2)] = 0;
					while (head->arg[i][j] != '"' && head->arg[i][j])
						tmp[k++] = head->arg[i][j++];
					j++;
					while (head->arg[i][j] != '"' && head->arg[i][j])
					{
						tmp[k++] = head->arg[i][j++];
						if (!head->arg[i][j] || (head->arg[i][j] != '"' && !head->arg[i][j + 1]))
						{
							free(tmp);
							freelexer(input);
							printf("Syntax Error: Unclosed Quote\n");
							return (NULL);
						}
					}
					j++;
					while (head->arg[i][j])
						tmp[k++] = head->arg[i][j++];
					free(head->arg[i]);
					head->arg[i] = ft_strdup(tmp);
					free(tmp);
					break ;
				}
				else if (head->arg[i][j] == '\'')
				{
					j = 0;
					k = 0;
					tmp = (char *)malloc(sizeof(char) * (ft_strlen(head->arg[i]) - 2));
					tmp[ft_strlen(head->arg[i] - 2)] = 0;
					while (head->arg[i][j] != '\'' && head->arg[i][j])
						tmp[k++] = head->arg[i][j++];
					j++;
					while (head->arg[i][j] != '\'' && head->arg[i][j])
					{
						tmp[k++] = head->arg[i][j++];
						if (!head->arg[i][j] || (head->arg[i][j] != '\'' && !head->arg[i][j + 1]))
						{
							free(tmp);
							freelexer(input);
							printf("Syntax Error: Unclosed Quote\n");
							return (NULL);
						}
					}
					j++;
					while (head->arg[i][j])
						tmp[k++] = head->arg[i][j++];
					free(head->arg[i]);
					head->arg[i] = ft_strdup(tmp);
					free(tmp);
					break ;
				}
				j++;
			}
			i++;
		}
		head = head->next;
	}
	// if (input)
	// {
	// 	printf("\n++++++++++\n\n");
	// 	for (int i = 0; input->arg[i]; i++)
	// 	{
	// 		printf("%d -- ", i);
	// 		for (int j = 0; input->arg[i][j]; j++)
	// 		{
	// 			printf("%d ", input->arg[i][j]);
	// 		}
	// 		printf("\n%s\n", input->arg[i]);
	// 	}
	// 	printf("\n++++++++++\n\n");
	// }
	return (input);
}
