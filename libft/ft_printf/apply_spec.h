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

#ifndef APPLY_SPEC_H
# define APPLY_SPEC_H

# define DEFAULT_FLOAT_PRECISION 6

char	*apply_spec(char *s, t_spec *spec);
char	*char_n_dup(char c, int n);
char	*add_prefix_free(char *s, char *prefix);
char	*add_suffix_free(char *s, char *suffix);

int		is_signed_conversion(t_spec spec);
int		is_numeric(t_spec spec);
int		is_nonfloat_numeric(t_spec spec);
char	*str_replace(char *s, char pattern, char replacement);
char	*add_suffix(char *s, char *suffix);

/*
**	apply_spec4.c
*/

char	*add_prefix(char *s, char *prefix);
char	*prepend_zeros(char *s, int n);
char	*str_insert(char *dst, char *src, int pos);
int		only_zeros(char *s);
char	*apply_hash(char *s, t_spec spec);

/*
**	apply_spec3.c
*/

char	*apply_plus(char *s, t_spec spec);
char	*apply_space(char *s, t_spec spec);
char	*apply_numeric_flags(char *s, t_spec spec);
int		len_after_dot(char *s);
char	*round_float(char *s, int precision);

/*
**	apply_spec2.c
*/

char	*float_precision(char *s, t_spec spec);
char	*apply_precision(char *s, t_spec spec);
char	*apply_fzero(char *s, t_spec spec);
char	*apply_fdash(char *s, t_spec spec);
char	*apply_width(char *s, t_spec spec);

#endif
