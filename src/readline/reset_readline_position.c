/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_readline_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:45 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 20:08:16 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		back_to_start_history_rp(void)
{
	if (rp(NULL)->history)
	{
		while (rp(NULL)->history->prev)
			rp(NULL)->history = rp(NULL)->history->prev;
	}
}

static void	reset_cur_pos_rp(void)
{
	rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
	rp(NULL)->cur_pos[1] = 1;
}

static void	parse_cur_pos(char *buf)
{
	size_t	i;

	i = 0;
	while (i < 32)
	{
		read(STDERR_FILENO, &buf[i], 1);
		if (buf[i] == 'R')
		{
			buf[i] = '\0';
			break ;
		}
		i++;
	}
}

static int	get_cursor_position(void)
{
	int		i;
	char	buf[32];
	char	*ptr_buf;

	i = 0;
	write(STDERR_FILENO, "\e[6n", 4);
	parse_cur_pos(buf);
	while (buf[i])
	{
		if (buf[i] == ';')
			break ;
		i++;
	}
	ptr_buf = buf;
	return (ft_atoi(ptr_buf + i + 1));
}

void		reset_rp_to_start(void)
{
	if (!(rp(NULL)->user_in = (char*)ft_memalloc(MIN_CMD_LENGTH)))
		reset_exit(1);
	rp(NULL)->max_len = MIN_CMD_LENGTH;
	rp(NULL)->len = 0;
	back_to_start_history_rp();
	rp(NULL)->prompt_len = get_cursor_position();
	rp(NULL)->in_readline = 1;
	reset_cur_pos_rp();
}
