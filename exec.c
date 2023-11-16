#include "ms.h"

int	exec_bin(char *line, char **envp)
{
	int		pidChild;
	int		signal_int;
	char	**arg;
	char	**env_paths;
	char	*path;
	int		i;

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
					exit (0);
			}
			else
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pidChild, &signal_int, 0);
				free_2d_arr(arg);
				return (signal_int);
			}
		}
		i++;
	}
	free_2d_arr(arg);
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
	free(tmp);
	free(path);
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
	free_2d_arr(tmp);
	return (cmdpaths);
}

void	free_2d_arr(char **arr_2d)
{
	int	i;

	i = 0;
	while (arr_2d[i])
	{
		free(arr_2d[i]);
		i++;
	}
	free(arr_2d);
}
