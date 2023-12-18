#include "ms.h"

int	redir_output(char *filename, int out_fd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	dup2(fd, out_fd);
	close(fd);
	return (0);
}

int	redir_output_append(char *filename, int out_fd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
	dup2(fd, out_fd);
	close(fd);
	return (0);
}

int	redir_input(char *filename, int in_fd)
{
	int		fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		return (-1);
	dup2(fd, in_fd);
	return (0);
}

int	redir_heredoc(char *delimiter, int in_fd)
{
	int		fd;
	int		pipe_fd[2];

	pipe(pipe_fd);
	fd = fork();
	if (fd == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		dup2(0, STDIN_FILENO);
		redir_heredoc_helper(delimiter, pipe_fd);
	}
	else
		waitpid(fd, 0, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], in_fd);
	return (0);
}

int	redir_heredoc_helper(char *delimiter, int *pipe_fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("-minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			exit(0);
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}	
	exit(1);
}
