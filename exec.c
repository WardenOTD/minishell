/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:06:25 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/02 17:27:02 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

// int	exec_bin(char *line, char **envp)
int	exec_bin(t_root *root, t_lexer *input)
{
	int		pidchild;
	char	**arg;
	char	**env_paths;
	char	*path;
	int		i;

	if (!ft_strncmp(input->arg[0], "", 1) || input->arg[0] == NULL)
		return (-2);
	arg = turn_arr_into_str(input->arg);
	i = 0;
	env_paths = get_env_paths(root->env);
	while (env_paths[i] != NULL)
	{
		arg[0] = append_path(env_paths[i], arg[0]);
		path = arg[0];
		signal(SIGINT, SIG_DFL);
		if (!(access(arg[0], X_OK)))
		{
			if (root->has_pipe == 0)
			{
				pidchild = fork();
				if (pidchild == 0)
				{
					if (execve(path, arg, envp) == -1)
						exit (2);
				}
				else
				{
					signal(SIGINT, SIG_IGN);
					return (exec_bin_parent(pidchild, arg, env_paths));
				}
			}
			else
				if (execve(path, arg, envp) == -1)
					exit (2);
		}
		i++;
	}
	free2d(arg);
	free2d(env_paths);
	return (-1);
}

int	exec_bin_parent(int pidchild, char **arg, char **env_paths)
{
	int	signal_int;

	waitpid(pidchild, &signal_int, 0);
	if (WIFSIGNALED(signal_int))
	{
		write(0, "\n", 1);
		g_status_code = (WTERMSIG(signal_int) + 128);
	}
	else
		g_status_code = WEXITSTATUS(signal_int);
	free2d(arg);
	free2d(env_paths);
	return (signal_int);
}

char	*append_path(char *cmdpath, char *input_line)
{
	char	**split_by_slash;
	char	*path;
	char	*full_cmd;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_strdup(cmdpath);
	split_by_slash = ft_split(input_line, '/');
	while (split_by_slash[i] != NULL)
		i++;
	tmp = ft_strjoin(path, "/");
	full_cmd = ft_strjoin(tmp, split_by_slash[i - 1]);
	free2d(split_by_slash);
	free(tmp);
	free(path);
	free(input_line);
	return (full_cmd);
}

char	**get_env_paths(t_env *env)
{
	char	**cmdpaths;
	t_env	*head;

	head = env;
	while (ft_strncmp(head->key, "PATH", 4))
		head = head->next;
	cmdpaths = ft_split(head->value, ':');
	return (cmdpaths);
}

char	**turn_arr_into_str(char **arr)
{
	char	*str;
	char	*tmp;
	int		i;
	char	**arg;

	i = 1;
	str = ft_strdup(arr[0]);
	while (arr[i])
	{
		tmp = ft_strjoin(str, "\7");
		free(str);
		str = ft_strjoin(tmp, arr[i]);
		free(tmp);
		i++;
	}
	arg = ft_split(str, '\7');
	free(str);
	return (arg);
}
