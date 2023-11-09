/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:57:52 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/09 15:59:19 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	cd(t_lexer *lexer, t_env *env)
{
	char	*target_pwd;
	char	*option;
	char	*oldpwd;
	int		cd_time;

	cd_time = 0;
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
			printf ("bash: cd: OLDPWD not set\n");
		else
			printf ("%s\n", target_pwd);
	}
	else
		target_pwd = option;

	if (get_env_value("HOME", env) == NULL && (get_arraysize(lexer->arg) == 1 || !ft_strncmp(option, "~", 1)))
		printf("bash: cd: HOME not set\n");
	else if (target_pwd == NULL && cd_time)
		add_oldpwd(lexer, env, oldpwd);
	else if (target_pwd == NULL && !cd_time)
		cd_time = 0;
	else if (chdir(target_pwd) == 0)
	{
		update_env(env, oldpwd, target_pwd);
		add_oldpwd(lexer, env, oldpwd);
		cd_time = 1;
	}
	else
		printf("bash: cd: %s: No such file or directory\n", target_pwd);

	free(option);
	return (0);
}

char *update_env(t_env *env, char *current, char *new)
{
	char *tmp;

	tmp = NULL;
	(void)current;
	while (ft_strncmp(env->key, "PWD", 4))
		env = env->next;
	if ((!ft_strncmp(new, get_env_value("HOME", env), 5) && new) || !ft_strncmp(new, "~", 1))
		tmp = new;
	else if (new == NULL)
		tmp = ft_strdup(current);
	else
	{
		tmp = ft_strjoin(env->value, "/");
		tmp = ft_strjoin(tmp, new);
	}
	env->value = tmp;
	return (env->value);
}

void add_oldpwd(t_lexer *lexer, t_env *env, char *oldpwd_str)
{
	t_env *new;

	(void)lexer;
	if (get_env_value("OLDPWD", env) == NULL)
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
}
