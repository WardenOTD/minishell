/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:30 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/20 13:14:18 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	display_env(t_env *env)
{
	while (env)
	{
		if (!env->value)
		{
			env = env->next;
			continue ;
		}
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

t_env	*get_env(t_env *env, char **envp)
{
	int		i;
	char	**tmp;
	t_env	*tmpp;
	t_env	*tail;

	tail = NULL;
	i = 0;
	while (envp[i] && i < 13)
	{
		tmp = ft_split(envp[i], '=');
		tmpp = envlstnew(tmp[0], tmp[1]);
		if (!env)
			env = tmpp;
		else
			tail->next = tmpp;
		tail = tmpp;
		free2d(tmp);
		i++;
	}
	return (env);
}

t_env	*add_env(t_env *env, t_lexer *input)
{
	char	**tmp;
	t_env	*head;
	t_env	*tail;

	tmp = env_split(input->arg[1]);
	head = NULL;
	tail = env;
	while (tail)
	{
		head = tail;
		// printf("add_env --- tmp[0]: %s, tail->key: %s\n", tmp[0], tail->key);
		if (!ft_strncmp(tmp[0], tail->key, ft_strlen(tmp[0])))
		{
			free(tail->value);
			tail->value = ft_strdup(tmp[1]);
			free2d(tmp);
			return (env);
		}
		tail = tail->next;
	}
	tail = head;
	head = envlstnew(tmp[0], tmp[1]);
	tail->next = head;
	free2d(tmp);
	return (env);
}

char *get_env_value(char *str, t_env *env)
{
	int 	len;
	char	*ret;
	char	*str2;

	ret = NULL;
	len = ft_strlen(str);
	if (str[0] == '$')
		str2 = &str[1];
	else
		str2 = str;
	while (env)
	{
		if (ft_strncmp(str2, env->key, len) == 0)
		{
			ret = ft_strdup(env->value);
			return (ret);
		}
		env = env->next;
	}
	return (NULL);
}

char	**env_split(char *arr)
{
	int		i;
	int		j;
	char	**ret;

	// printf("env_split:  __%s__\n", arr);
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
	{
		i++;
		j = i;
		while (arr[j])
			j++;
		ret[1] = (char *)malloc(sizeof(char) * (j - i + 1));
		ret[1][j - i] = 0;
		j = 0;
		while (arr[i])
			ret[1][j++] = arr[i++];
	}
	return (ret);
}

int env_is_valid(char *str, t_env *env)
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
