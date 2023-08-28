/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:15:29 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/22 11:44:16 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	out;
	int		sign;

	sign = 1;
	out = 0;
	while (*str == '\t' || *str == '\f' || *str == '\r'
		|| *str == '\v' || *str == ' ' || *str == '\n')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (out >= 214748364 && *str > '7' && sign == 1)
			return (-1);
		if (out >= 214748364 && *str > '8' && sign == -1)
			return (0);
		out = out * 10 + (*str - '0');
		str++;
	}
	return ((int)(out * sign));
}
