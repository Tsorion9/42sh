/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_print_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 08:15:05 by alexbuyanov       #+#    #+#             */
/*   Updated: 2021/01/06 23:52:07 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

int			check_big_list(int quantity_possibilities)
{
	char	buf[7];

	ft_printf("\nDisplay all %d possibilities? (y or n)",
		quantity_possibilities);
	if (read(0, buf, 7) == -1)
		return (1);
	if (buf[0] == 'y' || buf[0] == 9)
		return (0);
	return (1);
}

char		**create_buf_for_column_print(t_completion *matches)
{
	int		i;
	int		size;
	char	**buf;

	i = 0;
	size = 0;
	buf = NULL;
	if (!(size = complections_list_len(matches))
		|| !(buf = (char**)xmalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	buf[size] = NULL;
	while (matches)
	{
		buf[i++] = ft_strdup(matches->str);
		matches = matches->next;
	}
	return (buf);
}

void		com_api_print_lst(t_completion *matches)
{
	char		**buf;
	t_column	*cl;

	buf = NULL;
	cl = NULL;
	create_t_column(&cl);
	if (!(buf = create_buf_for_column_print(matches)) || !cl)
		return ;
	print_column(buf, cl);
	rp(NULL)->competitions_raws = cl->row_got + 1;
	free(cl);
	if (buf)
		del_array(buf);
}

int			complections_list_len(t_completion *matches)
{
	int	i;

	if (!matches)
		return (0);
	i = 1;
	while (matches->next)
	{
		matches = matches->next;
		i++;
	}
	return (i);
}
