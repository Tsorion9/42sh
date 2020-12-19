/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_print_many_suggestions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 08:15:05 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 08:25:39 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

void		com_api_print_many_suggestions(t_completion *matches)
{
	com_api_move_curs_to_end_line();
    ft_putchar('\n');
    com_api_print_lst(matches);
    gayprompt(rp(NULL)->prompt);
    ft_putstr(rp(NULL)->user_in);
    com_api_move_curs_to_prev_pos();
    inverse_search_index(rp(NULL)->cur_pos, rp(NULL)->index, rp(NULL)->prompt_len - 1);
}

void		com_api_print_normal_suggestions(t_completion *matches)
{
	com_api_move_curs_to_end_line();
    ft_putchar('\n');
    com_api_print_lst(matches);
    com_api_return_curs_to_line(complections_list_len(matches) + 1);
    com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
    com_api_move_curs_to_prev_pos();
}
