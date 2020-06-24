/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:15:38 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 20:15:40 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int			ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!a)
		return (w.ws_col);
	return (w.ws_row);
}

static void	processing_sigint(int signal_code)
{
	(void)signal_code;
	if (have_children_global_request(0, 0))
		write(2, "\n", 1);
	return ;
}

static void	processing_sigwinch(int signal_code)
{
	int	tmp_cur_pos[2];
	int	index;

	(void)signal_code;
	index = search_index();
	clear_all_line();
	rp(NULL)->ws_col = ret_winsize(0);
	rp(NULL)->ws_row = ret_winsize(1);
	clear_all_line();
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
	inverse_search_index(rp(NULL)->cur_pos, index);
	cur_pos_after_putstr(tmp_cur_pos);
	ret_cur_to_original_pos(tmp_cur_pos);
}

void		set_signal(void)
{
	signal(SIGINT, processing_sigint);
	signal(SIGWINCH, processing_sigwinch);
}
