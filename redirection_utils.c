/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:27:29 by jteoh             #+#    #+#             */
/*   Updated: 2024/01/04 11:27:30 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	**renew_arg_rm_redir(char **args)
{
	char	**new;
	int		i;
	int		max_len;

	i = 0;
	max_len = find_next_redir(args, 0);
	if (max_len == -1)
		return (args);
	new = malloc (sizeof(char *) * (max_len + 1));
	while (i < max_len)
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = NULL;
	free2d(args);
	return (new);
}
