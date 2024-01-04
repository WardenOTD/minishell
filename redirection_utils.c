/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:27:29 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 13:43:28 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	check_first_arg(char **args)
{
	if (!ft_strncmp(args[0], ">", 1) || !ft_strncmp(args[0], "<", 1))
	{
		free2d(args);
		return (1);
	}
	return (0);
}

char	**renew_arg_rm_redir(char **args)
{
	char	**new;
	int		i;
	int		max_len;

	i = 0;
	if (check_first_arg(args))
		return (NULL);
	max_len = find_next_redir(args, 0);
	if (max_len == -1)
		return (args);
	new = malloc (sizeof(char *) * (max_len + 1));
	while (i < max_len)
	{
		new[i] = ft_strdup(args[i]);
		printf("see: %s\n", new[i]);
		i++;
	}
	new[i] = NULL;
	free2d(args);
	return (new);
}
