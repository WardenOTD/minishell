/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:07:20 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/02 17:08:36 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	expand_flags_set(char arg, int *flag, int *dflag)
{
	if (arg == '\'')
	{
		if (*flag == 0)
			*flag = 1;
		else
			*flag = 0;
	}
	else if (arg == '\"')
	{
		if (*dflag == 0)
			*dflag = 1;
		else
			*dflag = 0;
	}
}

int	expand_helper_if(char *arg, int j, int flag, int dflag)
{
	if (arg[j + 1] == ' ' || arg[j + 1] == '"'
		|| arg[j + 1] == '\'' || arg[j + 1] == '$'
		|| !arg[j + 1])
	{
		if (arg[j + 1] == 0)
			return (0);
		if (flag == 0 && dflag == 0
			&& (arg[j + 1] == '"' || arg[j + 1] == '\''))
		{
			arg = remove_exp("$", arg);
			return (1);
		}
	}
	return (-1);
}

int	expand_helper_else_if(char *arg, int j, int flag, int dflag)
{
	if ((arg[j] == '$' && flag == 0) || (arg[j] == '$' && dflag == 1))
	{
		if (arg[j + 1] == '?')
		{
			arg = add_exp("$?", arg, ft_itoa(g_status_code));
			return (1);
		}
	}
	return (-1);
}

void	expand_helper_else(char *arg, t_env *env, int j)
{
	char	*ex;
	char	*val;
	int		count;

	count = 1;
	ex = NULL;
	val = NULL;
	while (arg[j] && arg[j] != ' '
		&& arg[j + 1] != '$' && arg[j] != '"'
		&& arg[j] != '\'')
	{
		count++;
		j++;
	}
	ex = expand_helper_else_helper(arg, count, j);
	val = get_env_value(ex, env);
	if (val == NULL)
		arg = remove_exp(ex, arg);
	else
		arg = add_exp(ex, arg, val);
	free(val);
	free(ex);
}

char	*expand_helper_else_helper(char *arg, int count, int j)
{
	char	*ex;

	ex = (char *)malloc(sizeof(char) * (count + 1));
	ex[count] = 0;
	j -= count - 1;
	count = 0;
	while (ex[count])
		ex[count++] = arg[j++];
	return (ex);
}
