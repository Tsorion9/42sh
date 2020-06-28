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

char	*w_ftoa(void *x, t_spec spec)
{
	return (ftoa(*(long double *)x, spec.precision));
}

char	*w_ctoa(void *x, t_spec spec)
{
	(void)spec;
	return (ctoa(*(char *)x));
}

char	*w_stoa(void *x, t_spec spec)
{
	(void)spec;
	return (stoa((char *)x));
}

char	*w_ptoa(void *x, t_spec spec)
{
	(void)spec;
	return (ptoa(x));
}

char	*w_percent(void *x, t_spec spec)
{
	(void)spec;
	(void)x;
	return (percent_to_a());
}
