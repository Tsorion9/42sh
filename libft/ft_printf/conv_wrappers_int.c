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

char	*w_itoa_b10u(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b10u(*(long long *)n));
}

char	*w_itoa_b10(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b10(*(long long *)n));
}

char	*w_itoa_b2(void *n, t_spec spec)
{
	(void)spec;
	return (itoa_b2(*(long long *)n));
}
