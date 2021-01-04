/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:15:38 by anton             #+#    #+#             */
/*   Updated: 2021/01/04 20:42:21 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

int			ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!a)
		return (w.ws_col);
	return (w.ws_row);
}

void	processing_sigint(int signal_code)
{
	int	user_in_lines;

	(void)signal_code;
	if (rp(NULL)->in_read)
	{
		user_in_lines = str_n(rp(NULL)->prompt_len) - rp(NULL)->cur_pos[1] + 2;
		while (user_in_lines-- > 0)
			write(STDERR_FILENO, "\n", 1);
		ft_memdel((void **)&(rp(NULL)->user_in));
		gayprompt(get_prompt(PS1));
		reset_rp_to_start(get_prompt(PS1));
	}
	return ;
}

void	processing_sigwinch(int signal_code)
{
	int	tmp_cur_pos[2];
	int	index;

	(void)signal_code;
	index = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	clear_all_line(rp(NULL)->prompt_len);
	rp(NULL)->ws_col = ret_winsize(0);
	rp(NULL)->ws_row = ret_winsize(1);
	clear_all_line(rp(NULL)->prompt_len);
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
	inverse_search_index(rp(NULL)->cur_pos, index, rp(NULL)->prompt_len);
	cur_pos_after_putstr(tmp_cur_pos, rp(NULL)->prompt_len);
	move_cursor_to_new_position(tmp_cur_pos, rp(NULL)->cur_pos);
}
