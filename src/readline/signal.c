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

int		ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!a)
		return (w.ws_col);
	return (w.ws_row);
}

void	set_sigint(void (*sigint_handler)(int))
{
	struct sigaction	sigint_action;

	sigaction(SIGINT, NULL, &sigint_action);
	if (sigint_handler)
		sigint_action.sa_handler = sigint_handler;
	else
		sigint_action.sa_handler = SIG_IGN;
	sigint_action.sa_flags = SA_NODEFER;
	sigaction(SIGINT, &sigint_action, NULL);
}

void	processing_sigint(int signal_code)
{
	(void)signal_code;
	return ;
}

void	processing_sigwinch(int signal_code)
{
	(void)signal_code;
	rp(NULL)->ws_col = ret_winsize(0);
	rp(NULL)->ws_row = ret_winsize(1);
	inverse_search_index(rp(NULL)->cur_pos, rp(NULL)->index,
	rp(NULL)->prompt_len);
}
