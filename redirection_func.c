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