/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:28 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/21 14:16:41 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*expand(t_lexer *input, t_env *env)
{
	t_lexer	*lhead;
	char	*ex;
	char	*val;
	int		count;
	int		i;
	int		j;
	int		flag;
	int		dflag;

	lhead = input;
	while (lhead)
	{
		i = 0;
		while (lhead->arg[i])
		{
			j = 0;
			flag = 0;
			dflag = 0;
			while (lhead->arg[i][j])
			{
				if (lhead->arg[i][j] == '\'')
				{
					if (flag == 0)
						flag = 1;
					else
						flag = 0;
				}
				if (lhead->arg[i][j] == '"')
				{
					if (dflag == 0)
						dflag = 1;
					else
						dflag = 0;
				}
				if ((lhead->arg[i][j] == '$' && flag == 0) || (lhead->arg[i][j] == '$' && dflag == 1))
				{
					if (lhead->arg[i][j + 1] == ' ' || lhead->arg[i][j + 1] == '"' || lhead->arg[i][j + 1] == '\''  || lhead->arg[i][j + 1] == '$' || !lhead->arg[i][j + 1])
					{
						if (lhead->arg[i][j + 1] == 0)
							break ;
						if (flag == 0 && dflag == 0 && (lhead->arg[i][j + 1] == '"' || lhead->arg[i][j + 1] == '\''))
						{
							lhead->arg[i] = remove_exp("$", lhead->arg[i]);
							j = 0;
							dflag = 0;
							flag = 0;
							continue ;
						}
						j++;
						continue ;
					}
					else if ((lhead->arg[i][j] == '$' && flag == 0) || (lhead->arg[i][j] == '$' && dflag == 1))
					{
						if (lhead->arg[i][j + 1] == '?')
						{
							lhead->arg[i] = add_exp("$?", lhead->arg[i], ft_itoa(g_status_code));
							j = 0;
							dflag = 0;
							flag = 0;
							continue ;
						}

					}
					else
					{
						count = 1;
						ex = NULL;
						val = NULL;
						while (lhead->arg[i][j] && lhead->arg[i][j] != ' ' && lhead->arg[i][j + 1] != '$' && lhead->arg[i][j] != '"' && lhead->arg[i][j] != '\'')
						{
							count++;
							j++;
						}
						ex = (char *)malloc(sizeof(char) * (count + 1));
						ex[count] = 0;
						j -= count - 1;
						count = 0;
						while (ex[count])
							ex[count++] = lhead->arg[i][j++];
						val = get_env_value(ex, env);
						if (val == NULL)
							lhead->arg[i] = remove_exp(ex, lhead->arg[i]);
						else
							lhead->arg[i] = add_exp(ex, lhead->arg[i], val);
						// if (val != NULL)
						free(val);
						free(ex);
						j = 0;
						dflag = 0;
						flag = 0;
						continue ;
					}
				}
				j++;
			}
			i++;
		}
		lhead = lhead->next;
	}
	return (input);
}

char	*remove_exp(char *needle, char *haystack)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = NULL;
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\'' || haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' ' || !haystack[i + j + 1]))
			{
				ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack) - ft_strlen(needle) + 1));
				ret[ft_strlen(haystack) - ft_strlen(needle)] = 0;
				k = -1;
				while (++k != i)
					ret[k] = haystack[k];
				i += j;
				while (haystack[++i])
					ret[k++] = haystack[i];
				free(haystack);
				free(needle);
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*add_exp(char *needle, char *haystack, char *val)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	ret = NULL;
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			if (needle[j + 1] == 0 && (haystack[i + j + 1] == '\'' || haystack[i + j + 1] == '"' || haystack[i + j + 1] == ' ' || haystack[i + j + 1] == '$' || !haystack[i + j + 1]))
			{
				ret = (char *)malloc(sizeof(char) * (ft_strlen(haystack) - ft_strlen(needle) + ft_strlen(val) + 1));
				ret[ft_strlen(haystack) - ft_strlen(needle) + ft_strlen(val)] = 0;
				k = -1;
				while (++k != i)
					ret[k] = haystack[k];
				i += j;
				j = 0;
				while (val[j])
					ret[k++] = val[j++];
				while (haystack[++i])
					ret[k++] = haystack[i];
				free(haystack);
				return (ret);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

t_lexer	*reorder(t_lexer *input)
{
	char	*tmp;
	t_lexer	*head;

	head = input;
	tmp = NULL;
	while (head)
	{
		// printf("\n\n-----\n\n");
		// for (int i = 0; head->arg[i]; i++)
		// 	printf("%s\n", head->arg[i]);
		// printf("\n-----\n\n");
		tmp = flatten_arr_w_space(head->arg);
		// printf("\n\n+++++\n%s\n+++++\n\n", tmp);
		head->arg = split2(tmp, ' ');
		free(tmp);
		head = head->next;
	}
	input = requote(input);
	return (input);
}
