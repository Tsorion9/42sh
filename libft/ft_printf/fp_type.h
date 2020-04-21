/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:52:53 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FP_TYPE_H
# define FP_TYPE_H

# include "printf.h"

typedef	void	*(*t_i_extr_fun)(t_spec s, va_list *l, long long *n);

int				is_usgn(t_spec spec);
void			*extr_sint(t_spec spec, va_list *vl, long long *p);
void			*extr_uint(t_spec spec, va_list *vl, long long *p);
t_i_extr_fun	choose_i_extr(t_spec spec);

#endif
