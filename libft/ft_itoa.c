/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:28:59 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/10 21:52:28 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_minitoa(void)
{
	char	*res;

	if (!(res = (char*)malloc(sizeof(char) * 12)))
		return (NULL);
	res[0] = '-';
	res[1] = '2';
	res[2] = '1';
	res[3] = '4';
	res[4] = '7';
	res[5] = '4';
	res[6] = '8';
	res[7] = '3';
	res[8] = '6';
	res[9] = '4';
	res[10] = '8';
	res[11] = '\0';
	return (res);
}

static int	ft_sitoa(int n)
{
	int		size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		size;
	int		sign;

	if (n == -2147483648)
		return (ft_minitoa());
	size = ft_sitoa(n);
	sign = 0;
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n < 0)
	{
		sign = 1;
		res[0] = '-';
		n *= -1;
	}
	res[size] = '\0';
	size--;
	while (size >= (0 + sign))
	{
		res[size] = (n % 10) + 48;
		n /= 10;
		size--;
	}
	return (res);
}
