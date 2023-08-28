/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteoh <jteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:56:37 by jteoh             #+#    #+#             */
/*   Updated: 2022/07/18 11:38:01 by jteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	digitcount(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (count + 1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*handleneg(unsigned int n)
{
	unsigned int	count;
	char			*arr;
	unsigned int	temp;

	count = digitcount(n);
	arr = (char *)malloc(count * sizeof(char) + 2);
	if (!arr)
		return (0);
	arr[count + 1] = '\0';
	while (count > 0)
	{
		temp = n % 10;
		n /= 10;
		arr[count] = temp + '0';
		count--;
	}
	arr[count] = '-';
	return (arr);
}

char	*ft_itoa(int n)
{
	unsigned int	count;
	char			*arr;
	int				temp;

	if (n < 0)
	{
		n *= -1;
		return (handleneg(n));
	}
	count = digitcount(n);
	arr = (char *)malloc(count * sizeof(char) + 1);
	if (!arr)
		return (0);
	arr[count--] = '\0';
	while (count > 0)
	{
		temp = n % 10;
		n /= 10;
		arr[count] = temp + '0';
		count--;
	}
	temp = n % 10;
	arr[count] = temp + '0';
	return (arr);
}
