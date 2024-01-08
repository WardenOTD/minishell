/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:41:33 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/08 18:10:28 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*lexer_to_str(t_root *root)
{
	char	*ret;
	char	*str;
	char	*tmp;
	t_lexer	*head;

	ret = NULL;
	head = root->input;
	while (head)
	{
		str = darr_to_arr_malloc(head->arg);
		if (head->next)
		{
			head = head->next;
			tmp = darr_to_arr_malloc(head->arg);
			ret = append_w_pipe_malloc(str, tmp);
			free(tmp);
		}
		else
			ret = append_w_pipe_malloc(ret, str);
		free(str);
		head = head->next;
	}
	root->input = freelexer(root->input);
	return (ret);
}

char	*darr_to_arr_malloc(char **darr)
{
	char	*arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!darr[i])
		return (NULL);
	while (darr[i])
	{
		j += ft_strlen(darr[i]);
		i++;
	}
	j += --i;
	arr = (char *)malloc(sizeof(char) * (j + 1));
	arr[j] = 0;
	arr = darr_to_arr_copy(darr, arr, i);
	return (arr);
}

char	*darr_to_arr_copy(char **darr, char *arr, int space)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (darr[i])
	{
		j = 0;
		while (darr[i][j])
			arr[k++] = darr[i][j++];
		if (space-- > 0)
			arr[k++] = ' ';
		i++;
	}
	return (arr);
}

char	*append_w_pipe_malloc(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*app;

	i = 0;
	j = 0;
	if (str1 != NULL)
		i = ft_strlen(str1);
	if (str2 != NULL)
		j = ft_strlen(str2);
	if (str1 && str2)
	{
		app = (char *)malloc(sizeof(char) * (i + j + 4));
		app[i + j + 3] = 0;
	}
	else
	{
		app = (char *)malloc(sizeof(char) * (i + j + 1));
		app[i + j] = 0;
	}
	app = append_w_pipe_copy(app, str1, str2);
	return (app);
}

char	*append_w_pipe_copy(char *app, char *str1, char *str2)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (str1)
		while (str1[++i])
			app[i] = str1[i];
	if (str1 && str2)
	{
		app[i++] = ' ';
		app[i++] = '|';
		app[i] = ' ';
	}
	if (str2)
		while (str2[j])
			app[++i] = str2[j++];
	return (app);
}
