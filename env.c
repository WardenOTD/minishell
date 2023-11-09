/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:30 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/09 15:18:56 by jutong           ###   ########.fr       */
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

	tmp = ft_split(input->arg[1], '=');
	head = NULL;
	tail = env;
	while (tail->next)
	{
		if (!ft_strncmp(tmp[0], tail->key, ft_strlen(tmp[0])))
		{
			free(tail->value);
			tail->value = ft_strdup(tmp[1]);
			free2d(tmp);
			return (env);
		}
		tail = tail->next;
	}
	head = envlstnew(tmp[0], tmp[1]);
	tail->next = head;
	free2d(tmp);
	return (env);
}

char *get_env_value(char *str, t_env *env)
{
	int 	len;
	char	*ret;

	ret = NULL;
	len = ft_strlen(str);
	while (env != NULL)
	{
		if (ft_strncmp(str, env->key, len) == 0)
			ret = ft_strdup(env->value);
		env = env->next;
	}
	return (ret);
}
