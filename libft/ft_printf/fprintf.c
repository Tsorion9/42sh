/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:03:03 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/24 20:14:24 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "apply_spec.h"
#include "read_spec.h"
#include "fp_type.h"

/*
**	Print all normal chars until % or '\0'
**	Return:
**	-pointer to first '%' if string contains '%'
**	-0 otherwise
*/

static const char	*print_until_percent(const char *format, int *i, int fd)
{
	while (*format && *format != '%')
	{
		ft_putchar_fd(*(format++), fd);
		(*i)++;
	}
	return (*format ? ++format : 0);
}

/*
**	Determine type of next arg according to spec
**	Extract argument from original vl
**	Return its string representation
*/

static char			*get_arg_str(t_spec *spec, va_list *vl)
{
	void		*arg;
	char		*res;
	t_conv_f	*action;
	int			error;

	error = 0;
	if (!(action = find_action(*spec)) ||
		!(arg = action->arg_extract(*spec, vl)) ||
		!(res = action->to_str(arg, *spec)))
		error = 1;
	if (action->cleanup_needed)
	{
		free(arg);
	}
	return (error || !(res = apply_spec(res, spec)) ? 0 : res);
}

static void			handle_stupid_c0_special_case(char *s,\
		t_spec spec, int *i, int fd)
{
	int	len;

	len = ft_strlen(s);
	s[len - 1] = 0;
	if (!spec.flag_dash)
	{
		ft_putstr_fd(s, fd);
		*i += ft_strlen(s);
		ft_putchar_fd('\0', fd);
		*i += 1;
	}
	else
	{
		ft_putchar_fd('\0', fd);
		*i += 1;
		*i += ft_strlen(s);
		ft_putstr_fd(s, fd);
	}
}

int					ft_fprintf(int fd, const char *format, ...)
{
	va_list		vl;
	t_spec		spec;
	char		*s;
	int			i;

	i = 0;
	va_start(vl, format);
	while ((format = print_until_percent(format, &i, fd)))
	{
		format = read_spec(format, &spec);
		if (!format || !(s = get_arg_str(&spec, &vl)))
			return (-1);
		if (spec.stupid_c0_special_case)
			handle_stupid_c0_special_case(s, spec, &i, fd);
		else
		{
			ft_putstr_fd(s, fd);
			i += ft_strlen(s);
		}
		free(s);
	}
	va_end(vl);
	return (i);
}
