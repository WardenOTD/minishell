#include "ms.h"

int	handle_redirect(char **args, t_fd_info* fd_info)
{
	int		token_pos;
	char	*token_type;
	int		i;

	i = 0;
	token_pos = find_next_redir(args, 0);
	if (token_pos == -1)
		return (1);
	while (args[i] != NULL)
	{
		if (find_next_redir(args, i) == -1)
			break ;
		token_pos = find_next_redir(args, i);
		token_type = ft_strdup(identify_token(args[token_pos]));
		if (do_redirections(token_type, args, token_pos, fd_info) == -1)
		{
			free(token_type);
			token_type = ft_strdup(identify_token(args[token_pos + 1]));
			printf("-minishell: syntax error near unexpected token '%s'\n", token_type);
			free(token_type);
			return (-1);
		}
		free(token_type);
		i = token_pos + 1;
	}
	return (0);
}

int	do_redirections(char *token_type, char **args, int token_pos, t_fd_info* fd_info)
{
	if (find_next_redir(args, token_pos) == token_pos && find_next_redir(args, token_pos + 1) == token_pos + 1)
		return (-1);
	if (!ft_strncmp(token_type, ">", 2))
		redir_output(args[token_pos + 1], fd_info->out_fd);
	else if (!ft_strncmp(token_type, ">>", 3))
		redir_output_append(args[token_pos + 1], fd_info->out_fd);
	else if (!ft_strncmp(token_type, "<", 3))
		redir_input(args[token_pos + 1], fd_info->in_fd);
	else if (!ft_strncmp(token_type, "<<", 3))
		redir_heredoc(args[token_pos + 1], fd_info->in_fd);
	return (0);
}

int	find_next_redir(char **args, int prev_i)
{
	int i;

	i = prev_i;
	while (args[i])
	{
		if (!ft_strncmp(args[i], ">", 2) || !ft_strncmp(args[i], "<", 2)
				|| !ft_strncmp(args[i], ">>", 3) || !ft_strncmp(args[i], "<<", 3))
			return (i);
		i++;
	}
	return (-1);
}

char	*identify_token(char *str)
{
	int i;

	i = 0;

	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return ("<<");
		return ("<");
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (">>");
		return (">");
	}
	return (NULL);
}
