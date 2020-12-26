/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_print_var_suggestions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 23:54:44 by nriker            #+#    #+#             */
/*   Updated: 2020/12/26 21:35:07 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

void		com_api_print_var_lst(t_completion *matches)
{
	while (matches)
	{
		ft_putstr(matches->str);
		ft_putchar('\n');
		matches = matches->next;
	}
}

void		com_api_print_many_var_suggestions(t_completion *matches)
{
	com_api_move_curs_to_end_line();
    if (check_big_list(complections_list_len(matches)))
    {
        ft_putchar('\n');
        rp(NULL)->competitions_raws = 2;
	    com_api_return_curs_to_line();
        com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
        com_api_move_curs_to_prev_pos();
		com_api_clear_till_end();
        return ;
    }
    ft_putchar('\n');
    com_api_print_var_lst(matches);
    gayprompt(rp(NULL)->prompt);
	readline_putstr(rp(NULL)->user_in, rp(NULL)->cur_pos, rp(NULL)->prompt_len);
    com_api_move_curs_to_prev_pos();
}

void		com_api_print_normal_var_suggestions(t_completion *matches)
{
	com_api_move_curs_to_end_line();
    ft_putchar('\n');
    com_api_print_var_lst(matches);
	rp(NULL)->competitions_raws = complections_list_len(matches) + 1;
    com_api_return_curs_to_line();
    com_api_return_curs_to_position(rp(NULL)->column_end_of_line);
    com_api_move_curs_to_prev_pos();
}

void		com_api_print_var_suggestion(t_completion *matches, char *remainder_word,
								char *path)
{
	int				size_of_matches;

	size_of_matches = complections_list_len(matches);
	if (size_of_matches == 1)
		complete_word(matches, remainder_word, path);
	else
	{
		if (size_of_matches > 20)
			com_api_print_many_var_suggestions(matches);
		else if (size_of_matches > 1)
			com_api_print_normal_var_suggestions(matches);
	}
}
