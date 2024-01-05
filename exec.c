/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:06:25 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/06 00:35:41 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	exec_bin(t_root *root, t_lexer *input)
{
	int		pidchild;
	char	**arg;
	char	*path;
	int		i;

	pidchild = 0;
	if (!ft_strncmp(input->arg[0], "", 1) || input->arg[0] == NULL)
		return (-2);
	arg = turn_arr_into_str(input->arg);
	i = 0;
	root->env_paths = get_env_paths(root->env);
	if (root->env_paths == NULL)
		return (-1);
	while (root->env_paths[i] != NULL)
	{
		if (ft_strncmp(arg[0] , "./", 2))
			arg[0] = append_path(root->env_paths[i], arg[0]);
		path = arg[0];
		signal(SIGINT, SIG_DFL);
		if (!(access(arg[0], X_OK)))
			return (exec_bin_helper(root, path, pidchild, arg));
		i++;
	}
	free2d(arg);
	free2d(root->env_paths);
	return (-1);
}

int	exec_bin_helper(t_root *root, char *path, int pidchild, char **arg)
{
	if (root->has_pipe == 0)
	{
		pidchild = fork();
		if (pidchild == 0)
		{
			if (execve(path, arg, root->envp) == -1)
				exit (2);
		}
		else
		{
			signal(SIGQUIT, ctrlslash);
			signal(SIGINT, SIG_IGN);
			return (exec_bin_parent(pidchild, arg, root->env_paths));
		}
	}
	else
		if (execve(path, arg, root->envp) == -1)
			exit (2);
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
	while (head)
	{
		if (!ft_strncmp(head->key, "PATH", 5))
			break ;
		head = head->next;
		if (head == NULL)
			return (NULL);
	}
	cmdpaths = ft_split(head->value, ':');
	return (cmdpaths);
}
