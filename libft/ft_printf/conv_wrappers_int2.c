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

#include "printf.h"

char	*w_itoa_b8(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b8(*(long long *)n));
}

char	*w_itoa_xx(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_bxx(*(long long *)n));
}

char	*w_itoa_x(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_bx(*(long long *)n));
}
