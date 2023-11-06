/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutong <jutong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:32:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/11/06 23:27:34 by jutong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	call(t_lexer *input, t_env *env)
{
	if (!ft_strncmp(input->token[0], "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->token[0], "pwd", 5))
		ft_pwd();
	else if (!ft_strncmp(input->token[0], "cd", 3))
		cd(input, env);
}
