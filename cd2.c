/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:21:32 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:21:53 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	add_oldpwd(t_lexer *lexer, t_env *env, char *oldpwd_str)
{
	t_env	*new;
	char	*oldpwd_value;

	(void)lexer;
	oldpwd_value = get_env_value("OLDPWD", env);
	if (oldpwd_value == NULL)
	{
		while (env->next)
			env = env->next;
		new = envlstnew("OLDPWD", oldpwd_str);
		env->next = new;
	}
	else
	{
		while (ft_strncmp("OLDPWD", env->key, 6))
			env = env->next;
		free(env->value);
		env->value = ft_strdup(oldpwd_str);
	}
	free (oldpwd_value);
}
