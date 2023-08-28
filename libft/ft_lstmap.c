/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:27:05 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/18 16:40:41 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*new;
	t_list	*elem;

	if (!lst)
		return (0);
	new = 0;
	while (lst != 0)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			ft_lstclear(&new, d);
			return (0);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
