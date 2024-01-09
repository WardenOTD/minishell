/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:30 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/09 15:35:38 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	display_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (!head->value)
		{
			head = head->next;
			continue ;
		}
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

t_env	*get_env(t_env *env, char **envp)
{
	int		i;
	char	**tmp;
	t_env	*tmpp;
	t_env	*tail;

	i = 0;
	tail = NULL;
	while (envp[i])
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
	env = shlvl(env);
	return (env);
}

t_env	*add_env(t_env *env, char *arg)
{
	char	**tmp;
	t_env	*head;
	t_env	*tail;

	tmp = env_split(arg);
	head = NULL;
	tail = env;
	while (tail)
	{
		head = tail;
		if (!ft_strncmp(tmp[0], tail->key, ft_strlen(tmp[0]) + 1))
			return (add_env_helper(env, tail, tmp));
		tail = tail->next;
	}
	tail = head;
	head = envlstnew(tmp[0], tmp[1]);
	tail->next = head;
	free2d(tmp);
	return (env);
}

t_env	*add_env_helper(t_env *env, t_env *tail, char **tmp)
{
	if (tail->value)
		free(tail->value);
	if (tmp[1])
		tail->value = ft_strdup(tmp[1]);
	else
		tail->value = NULL;
	free2d(tmp);
	return (env);
}

char	*get_env_value(char *str, t_env *env)
{
	t_env	*head;
	int		len;
	char	*ret;
	char	*str2;

	head = env;
	ret = NULL;
	if (str[0] == '$')
		str2 = &str[1];
	else
		str2 = str;
	len = ft_strlen(str2);
	while (head)
	{
		if (ft_strncmp(str2, head->key, len + 1) == 0)
		{
			ret = ft_strdup(head->value);
			return (ret);
		}
		head = head->next;
	}
	return (NULL);
}
