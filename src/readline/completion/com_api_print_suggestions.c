/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_print_suggestions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:25:58 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 13:18:04 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

char		**create_buf_for_column_print(t_completion *matches)
{
	int		i;
	int		size;
	char	**buf;

	i = 0;
	buf = NULL;
	if (!(size = complections_list_len(matches))
		|| !(buf = (char**)malloc(sizeof(char*) * size + 1)))
		return NULL;
	buf[size] = NULL;
	while (matches)
	{
		buf[i++] = ft_strdup(matches->str);
		matches = matches->next;
	}
	return buf;
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
	free_buf(buf);
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

void		com_api_clear_till_end(void)
{
	com_api_move_curs_to_end_line();
	ft_putchar('\n');
	tc_clear_till_end();
	rp(NULL)->competitions_raws = 1;
	com_api_return_curs_to_line();
	com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
	com_api_move_curs_to_prev_pos();
}

void		com_api_print_suggestion(t_completion *matches, char *remainder_word,
								char *path)
{
	static t_deque	*tokbuf_g;
	t_deque			*tokbuf_l;

	tokbuf_g = NULL;
	tokbuf_l = NULL;
	if (!matches)
		return ;
	if (complections_list_len(matches) == 1)
		complete_word(matches, remainder_word, path);
	else
	{
		if (complections_list_len(matches) > 20)
		{
			com_api_print_many_suggestions(matches);
		}
		else if (complections_list_len(matches) > 1)
			com_api_print_normal_suggestions(matches);
	}
}
