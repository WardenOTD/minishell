/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:30 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 00:00:11 by jutong           ###   ########.fr       */
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
	tmpp = (t_env *)malloc(sizeof(t_env));
	tail = (t_env *)malloc(sizeof(t_env));
	while (envp[i] && i <= 12)
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

char *get_env_value(char *str, t_env *env)
{
	int 	len;
	char	*ret;

	ret = NULL;
	len = ft_strlen(str);
	while (env->next)
	{
		if (ft_strncmp(str, env->key, len) == 0)
			ret = ft_strdup(env->value);
		env = env->next;
	}
	return (ret);
}
