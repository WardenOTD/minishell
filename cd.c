/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:57:52 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 12:21:47 by jteoh            ###   ########.fr       */
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
		option = lexer->arg[1];
	else if (get_arraysize(lexer->arg) > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		return (0);
	}
	target_pwd = get_target_path(lexer, env, envp, option);
	cd_detect_error(lexer, env, target_pwd, option);
	if (target_pwd && get_arraysize(lexer->arg) == 1)
		free(target_pwd);
	return (0);
}

char	*cd_detect_error(t_lexer *lexer, t_env *env,
	char *target_pwd, char *option)
{
	char	*oldpwd;

	(void)option;
	oldpwd = getcwd(NULL, 0);
	if (target_pwd == NULL && (get_arraysize(lexer->arg) == 1))
		printf("bash: cd: HOME not set\n");
	else if (target_pwd == NULL && !ft_strncmp(option, "-", 2))
		printf("bash: cd: OLDPWD not set\n");
	else if (chdir(target_pwd) == 0)
	{
		update_env(env, oldpwd, target_pwd);
		add_oldpwd(lexer, env, oldpwd);
		if (option != NULL)
			if (!ft_strncmp(option, "~", 1) || !ft_strncmp(option, "-", 1))
				free (target_pwd);
	}
	else
		printf("bash: cd: %s: No such file or directory\n", target_pwd);
	free(oldpwd);
	return (NULL);
}

char	*get_target_path(t_lexer *lexer, t_env *env, char **envp, char *option)
{
	char	*target_pwd;
	char	**tmp;

	if (get_arraysize(lexer->arg) == 1 && env_is_valid("HOME", env))
		target_pwd = get_env_value("HOME", env);
	else if (get_arraysize(lexer->arg) == 1 && !env_is_valid("HOME", env))
		target_pwd = NULL;
	else if (!ft_strncmp(option, "~", 1))
	{
		tmp = get_target_pwd_helper(envp);
		target_pwd = ft_strdup(tmp[1]);
		free2d(tmp);
	}
	else if (!ft_strncmp(option, "-", 1))
	{
		target_pwd = get_env_value("OLDPWD", env);
		if (target_pwd != NULL)
			printf("%s\n", target_pwd);
	}
	else
		target_pwd = option;
	return (target_pwd);
}

char	**get_target_pwd_helper(char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (ft_strncmp(envp[i], "HOME", 4))
		i++;
	tmp = ft_split(envp[i], '=');
	return (tmp);
}

char	*update_env(t_env *env, char *current, char *neww)
{
	char	*tmp;

	tmp = NULL;
	while (ft_strncmp(env->key, "PWD", 4))
		env = env->next;
	if (neww == NULL)
		tmp = ft_strdup(current);
	else
	{
		tmp = ft_strjoin(env->value, "/");
		tmp = ft_strjoin_free(tmp, neww);
	}
	if (env->value)
		free(env->value);
	env->value = ft_strdup(tmp);
	free(tmp);
	return (env->value);
}
