/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_print_suggestions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:25:58 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/13 23:37:59 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		com_api_print_lst(t_completion *matches)
{
	while (matches)
	{
		ft_putstr(matches->str);
		ft_putchar('\n');
		matches = matches->next;
	}
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
	com_api_return_curs_to_line(1);
	com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
	com_api_move_curs_to_prev_pos();
}

void		com_api_print_suggestion(t_completion *matches, char *remainder_word,
								char *path)
{
	if (!matches)
		return ;
	if (complections_list_len(matches) == 1)
		complete_word(matches, remainder_word, path);
	else
	{
		if (complections_list_len(matches) >= 20)
		{
			ft_putchar('\n');
			com_api_print_lst(matches);
			// ft_putstr("Many suggestions!");
		}
		else if (complections_list_len(matches) > 1)
		{
			com_api_move_curs_to_end_line();
			ft_putchar('\n');
			com_api_print_lst(matches);
			com_api_return_curs_to_line(complections_list_len(matches) + 1);
			com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
			com_api_move_curs_to_prev_pos();
			// ft_putstr("<20 suggestions!");
		}
	}
}
