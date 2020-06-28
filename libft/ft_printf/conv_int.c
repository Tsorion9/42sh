/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 14:55:10 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Here you can find declarations of integer conversion functions
*/

#include "printf.h"
#include "libft.h"

#define BINARY "01"
#define OCTAL "01234567"
#define DECIMAL "0123456789"
#define HEX_L "0123456789abcdef"
#define HEX_U "0123456789ABCDEF"

char	*itoa_b10u(long long n)
{
	return (ft_itoa_base(n, DECIMAL, 0));
}

char	*itoa_b10(long long n)
{
	return (ft_itoa_base(n, DECIMAL, 1));
}

char	*itoa_b2(long long n)
{
	return (ft_itoa_base(n, BINARY, 0));
}
