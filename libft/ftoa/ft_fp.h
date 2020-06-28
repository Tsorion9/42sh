/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:46:40 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:46:42 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FP_H
# define FT_FP_H

# define LD_MAX_DIGITS 20000
# define CRUTCH_FLOAT_PRECISION_CONSTANT 30

/*
**	Example:
**  buff		start	end
**	 |			|		 |
**	 V			V		 V
**   ..garbage..1234512345
**	after_dot = 5
**	is_negative = 1
**	encodes:  -12345.12345
**
**	end points to last digit
**	Store digits, not ascii codes
*/

typedef struct			s_decimal
{
	char				buff[LD_MAX_DIGITS];
	char				*end;
	char				*start;
	int					after_dot;
	int					is_negative;
}						t_decimal;

typedef struct			s_float
{
	unsigned long int	mant;
	unsigned short		exp;
	unsigned short		sign;
	unsigned long int	mant_mask;
	int					mask_shift;
	int					precision;
}						t_float;

char					*ftoa(long double x, int precision);
void					fill_t_float(long double x, t_float *num, \
								int precision);
int						abs_(int x);
void					cut_float(t_float *num, int *power_of2);
char					*eval_power_sum(t_float *num, int power_of2);
char					*normal_case(t_float *num);
char					*exp_all_zeros(t_float *num);
char					*exp_all_ones(t_float *num);

void					insert_point(int after_dot, char *s);
int						to_ascii(t_decimal repr, char *s);
int						nchar_after_dot(char *s);
int						ndigits(char *s);
void					copy_digits_numbers(char *src, char *dst);
void					positive_ascii_to(t_decimal *repr, char *s);
int						shift_excessive_digits(t_decimal *a, \
								t_decimal *b, char *tmp);
void					single_digit_a(t_decimal *a, char **res, int *carry);
void					single_digit_b(t_decimal *b, char **res, int *carry);
void					single_digit_both(t_decimal *a, \
								t_decimal *b, char **res, int *carry);
void					adder_decimal(t_decimal *a, t_decimal *b, char *res);
void					copy_from_buf(char *buf, t_decimal *a);
int						max(int a, int b);
void					add_positive_decimal(t_decimal *a, t_decimal *b);
void					mul_digit(t_decimal *a, t_decimal *b,\
								int degree, t_decimal *partial_product);
void					copy_t_decimal(t_decimal *src, t_decimal *dst);
void					adjust_dot_if_needed(t_decimal *a);

void					multiply_positive_decimal(t_decimal *a, t_decimal *b);

void					init_t_decimal(t_decimal *x);
void					square_positive_decimal(t_decimal *x);
void					power_positive_decimal(t_decimal *x, int pow);

#endif
