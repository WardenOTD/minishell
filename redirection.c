#include "ms.h"

void	handle_redir(t_lexer *input, t_env *env, t_exp *exp, char *line, char **envp)
{
	char	**tmp;
	char	*redir_cmd;

	if (redir_cmd = find_redir_command(input->arg) == NULL)
		return ;
	tmp = ft_split(input->arg, redir_cmd);
}

char	*find_redir_command(char **arg)
{
	int	i;

	i = 0;
	while(arg[1][i])
	{
		if (arg[1][i] == "<")
			return ("<");
		else if (arg[1][i] == ">")
			return (">");
		else if (arg[1][i] == "<<")
			return ("<<");
		else if (arg[1][i] == ">>")
			return (">>");
		i++;
	}
	return (NULL);
}