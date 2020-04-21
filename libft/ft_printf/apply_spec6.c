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
#include "apply_spec.h"

/*
**  "+" " " "#"
*/

char	*apply_numeric_flags(char *s, t_spec spec)
{
	if (spec.conv == 'p')
		return ((s = apply_hash(s, spec)));
	if (is_numeric(spec) &&\
		(s = apply_hash(s, spec)) && \
		(s = apply_plus(s, spec)) && \
		(s = apply_space(s, spec)))
		return (s);
	return (s);
}
