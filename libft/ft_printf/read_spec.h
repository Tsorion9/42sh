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

#ifndef READ_SPEC_H
# define READ_SPEC_H

# include "printf.h"

const char	*read_spec(const char *format, t_spec *spec);
const char	*read_conv_spec(const char *f, t_spec *spec);
const char	*read_length(const char *f, t_spec *spec);
const char	*read_precision(const char *f, t_spec *spec);
const char	*read_width(const char *f, t_spec *spec);
const char	*read_flags(const char *f, t_spec *spec);
void		read_flag(const char c, t_spec *spec);
void		init_spec(t_spec *spec);

#endif
