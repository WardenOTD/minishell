#include "ms.h"

int	check_available_redir(char *args);
// int	run_redir(t_lexer *input, t_env *env, t_exp *exp, char *line, char **envp, char *token);

int	run_cmd(t_lexer *input, t_env *env, t_exp *exp, char *line, char **envp)
{
	int i = 0;
	// int j = 0;
	// char *redir = NULL;
	(void) line;
	char **cmd = input->arg;

	while (cmd[i])
	{
		if (!check_available_redir(cmd[i]))
		{
			call(input, env, exp, envp);
			return (0);
		}
		// redir = identify_token;

		i++;
	}
	return (0);
}


int	check_available_redir(char *args)
{
	int i = 0;

	while (args[i])
	{
		if (args[i] == '<' || args[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

char	*identify_token(char *str, int pos)
{
	int i;

	i = pos;

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