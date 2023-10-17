/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:35:30 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/17 13:50:47 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	display_env(t_env *env)
{
	int	i;

	i = -1;
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

void	get_env(t_env *env, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (!env)
			printf("enter env new\n");
			env = envlstnew(env);
			printf("exit env new\n");
		printf("before append\n");
		env = envlstappend(env, tmp[0], tmp[1]);
		printf("after append\n");
		free (tmp);
		env = env->next;
		i++;
	}
}
