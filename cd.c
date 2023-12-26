/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:57:52 by jteoh             #+#    #+#             */
/*   Updated: 2023/12/26 11:54:25 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	cd(t_lexer *lexer, t_env *env, char **envp)
{
	char	*target_pwd;
	char	*option;

	target_pwd = NULL;
	option = NULL;
	if (get_arraysize(lexer->arg) == 2)
		option = ft_strdup(lexer->arg[1]);
	else if (get_arraysize(lexer->arg) > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		return (0);
	}

	target_pwd = get_target_path(lexer, env, envp, option);
	cd_detect_error(lexer, env, target_pwd, option);

	free(option);
	return (0);
}

char *cd_detect_error(t_lexer *lexer, t_env *env, char *target_pwd, char *option)
{
	char *oldpwd;

	(void)option;
	oldpwd = getcwd(NULL, 0);
	if (target_pwd == NULL && (get_arraysize(lexer->arg) == 1))
		printf("bash: cd: HOME not set\n");
	else if (target_pwd == NULL)
	{
		printf("bash: cd: OLDPWD not set\n");
		add_oldpwd(lexer, env, oldpwd);
	}
	else if (chdir(target_pwd) == 0)
	{
		update_env(env, oldpwd, target_pwd);
		add_oldpwd(lexer, env, oldpwd);
	}
	else
		printf("bash: cd: %s: No such file or directory\n", target_pwd);
	return (NULL);
}

char *get_target_path(t_lexer *lexer, t_env *env, char **envp, char *option)
{
	char	*target_pwd;
	int		i;
	char	**tmp;

	target_pwd = NULL;
	if (get_arraysize(lexer->arg) == 1 && env_is_valid("HOME", env))
		target_pwd = get_env_value("HOME", env);
	else if (get_arraysize(lexer->arg) == 1 && !env_is_valid("HOME", env))
		target_pwd = NULL;
	else if (!ft_strncmp(option, "~", 1))
	{
		i = 0;
		while (ft_strncmp(envp[i], "HOME", 4))
			i++;
		tmp = ft_split(envp[i], '=');
		target_pwd = ft_strdup(tmp[1]);
		free2d(tmp);
	}
	else if (!ft_strncmp(option, "-", 1))
	{
		target_pwd = get_env_value("OLDPWD", env);
		printf("%s\n", target_pwd);
	}
	else
		target_pwd = option;
	return (target_pwd);
}

char *update_env(t_env *env, char *current, char *new)
{
	char *tmp;

	tmp = NULL;
//	(void)current;
	while (ft_strncmp(env->key, "PWD", 4))
		env = env->next;
	if (new == NULL)
		tmp = ft_strdup(current);
	else
	{
		tmp = ft_strjoin(env->value, "/");
		tmp = ft_strjoin(tmp, new);
	}
	env->value = tmp;
	free(tmp);
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
