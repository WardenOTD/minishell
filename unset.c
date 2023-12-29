#include "ms.h"

void	unset(t_lexer *lexer, t_env *env)
{
	int		i;
	char	*remove;

	i = 1;
	remove = NULL;

	if (get_arraysize(lexer->arg) == 1)
		return ;
	while (lexer->arg[i] != NULL)
	{
		remove = ft_strdup(lexer->arg[i]);
		remove_node(&env, remove);
		free(remove);
		i++;
	}
}

void	remove_node(t_env **env, char *remove)
{
	t_env	*tmp;
	t_env	*prev;

	prev = *env;
	tmp = prev;
	if (!ft_strncmp(tmp->key, remove, ft_strlen(remove)) && tmp)
	{
		(*env) = (*env)->next;
		free(tmp->value);
		tmp->value = NULL;
		return ;
	}
	while (ft_strncmp(tmp->key, remove, ft_strlen(remove)) && tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->key, remove, ft_strlen(remove)))
	{
		prev->next = tmp->next;
		free_node(tmp);
	}
}

void	free_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}