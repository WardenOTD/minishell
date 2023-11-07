/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:57:52 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/07 14:57:54 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int get_arraysize(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	cd(t_lexer *lexer, t_env *env)
{
	char *target_pwd;
	char *option;
	char *oldpwd;

	target_pwd = NULL;
	option = NULL;
	oldpwd = getcwd(NULL, 0);

	if (get_arraysize(lexer->arg) == 2)
		option = ft_strdup(lexer->arg[1]);
	else if (get_arraysize(lexer->arg) > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (0);
	}

	if (get_arraysize(lexer->arg) == 1 || !ft_strncmp(option, "~", 1))
		target_pwd = get_env_value("HOME", env);

	else if (!ft_strncmp(option, "-", 1))
	{
		target_pwd = get_env_value("OLDPWD", env);
		if (target_pwd == NULL)
			printf ("bash: cd : OLDPWD not set\n");
		else
			printf ("%s\n", target_pwd);
	}

	else
		target_pwd = option;

	if (chdir(target_pwd) == 0 || target_pwd == NULL)
		update_env(env, oldpwd, target_pwd);
	else
		printf("bash: cd: %s: No such file or directory\n", target_pwd);

	// export OLDPWD = oldpwd;

	return (0);
}

char *update_env(t_env *env, char *current, char *new)
{
	char *tmp;

	tmp = NULL;
	(void)current;
	while (ft_strncmp(env->key, "PWD", 4))
		env = env->next;
	if (new == NULL || ft_strncmp(new, "~", 1))
		tmp = new;
	else
		tmp = ft_strjoin(env->value, new);
	env->value = tmp;
	return (env->value);
}
