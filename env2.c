/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:22:31 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:22:36 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	**env_split(char *arr)
{
	int		i;
	char	**ret;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * 3);
	ret[2] = NULL;
	while (arr[i] && arr[i] != '=')
		i++;
	ret[0] = (char *)malloc(sizeof(char) * (i + 1));
	ret[0][i] = 0;
	i = 0;
	while (arr[i] && arr[i] != '=')
	{
		ret[0][i] = arr[i];
		i++;
	}
	if (arr[i] == 0)
		ret[1] = NULL;
	else
		ret = env_split_helper(i, arr, ret);
	return (ret);
}

char	**env_split_helper(int i, char *arr, char **ret)
{
	int	j;

	i++;
	j = i;
	if (arr[j] == 0)
	{
		ret[1] = ft_strdup("");
		return (ret);
	}
	while (arr[j])
		j++;
	ret[1] = (char *)malloc(sizeof(char) * (j - i + 1));
	ret[1][j - i] = 0;
	j = 0;
	while (arr[i])
		ret[1][j++] = arr[i++];
	return (ret);
}

int	env_is_valid(char *str, t_env *env)
{
	int	len;

	len = ft_strlen(str);
	while (env != NULL)
	{
		if (ft_strncmp(str, env->key, len) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

t_env	*free_env(t_env *env)
{
	t_env	*head;
	t_env	*tmp;
	t_env	*tmpnxt;

	head = env;
	tmp = head->next;
	while (tmp)
	{
		tmpnxt = tmp->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = tmpnxt;
	}
	free(head->key);
	if (head->value)
		free(head->value);
	free(head);
	env = NULL;
	return (env);
}
