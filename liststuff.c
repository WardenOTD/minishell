/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liststuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:31:18 by jteoh             #+#    #+#             */
/*   Updated: 2023/10/13 15:37:27 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_lexer	*lexerlstnew(t_lexer *head)
{
	head = (t_lexer *)malloc(sizeof(t_lexer));
	if (head->next)
		return (lexerlstnew(head->next));
	else
		head->next = (t_lexer *)malloc(sizeof(t_lexer));
	return (head->next);
}

t_lexer	*envlstnew(t_env *head)
{
	head = (t_env *)malloc(sizeof(t_env));
	if (head->next)
		return (envlstnew(head->next));
	else
		head->next = (t_env *)malloc(sizeof(t_env));
	return (head->next);
}
