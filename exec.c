#include "ms.h"

// int	exec_bin(char *line, char **envp)
int	exec_bin(t_lexer *input, char **envp)
{
	int		pidChild;
	char	*line;
	char	**arg;
	char	**env_paths;
	char	*path;
	int		i;

	line = turn_arr_into_str(input->arg);
	i = 0;
	arg = ft_split(line, ' ');
	env_paths = get_env_paths(envp);
	while(env_paths[i] != NULL)
	{
		arg[0] = append_path(env_paths[i], arg[0]);
		path = arg[0];
		signal(SIGINT, SIG_DFL);
		if (!(access(arg[0], X_OK)))
		{
			pidChild = fork();
			if (pidChild == 0)
			{
				if (execve(path, arg, envp) == -1)
					exit (2);
			}
			else
			{
				signal(SIGINT, SIG_IGN);		
				return (exec_bin_parent(pidChild, line, arg, env_paths));
			}
		}
		i++;
	}
	free(line);
	free2d(arg);
	free2d(env_paths);
	return (-1);
}

int	exec_bin_parent(int pidChild, char *line, char **arg, char **env_paths)
{
	int	signal_int;

	waitpid(pidChild, &signal_int, 0);
	free(line);
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

char	**get_env_paths(char **envp)
{
	char	**tmp;
	char	**cmdpaths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	tmp = ft_split(envp[i], '=');
	cmdpaths = ft_split(tmp[1], ':');
	free2d(tmp);
	return (cmdpaths);
}

char *turn_arr_into_str(char **arr)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 1;
	str = ft_strdup(arr[0]);
	while (arr[i])
	{
		tmp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(tmp, arr[i]);
		free(tmp);
		i++;
	}
	return (str);
}
