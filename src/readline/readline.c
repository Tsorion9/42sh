/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:42 by mphobos           #+#    #+#             */
/*   Updated: 2021/01/08 14:00:32 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "gayprompt.h"

void		reset_exit(int status);

int			is_print(long c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}

static void	handle_click_sup(long c)
{
	if (!now_search_history())
	{
		if (c == CTRL_LEFT || c == CTRL_RIGHT)
			wordmove_cursor(c);
		else if (c == CTRL_UP || c == CTRL_DOWN)
			strmove_cursor(c);
		else if (c == CTRL_W)
			delete_last_word();
		else if (c == SHIFT_TAB)
			add_symbol(' ');
		else if (c == HOME || c == END)
			home_end(c);
		else if (c == UP_ARROW || c == DOWN_ARROW)
			up_down_arrow(c);
		else if (c == TAB_ARROW)
			completion();
		else if (c == BACKSPACE)
			delete_symbol();
		else if (c == DEL)
			delete_symbol_forward();
		else if (is_print(c))
			add_symbol(c);
		else if (c == ALT_LEFT_ARROW || c == ALT_RIGHT_ARROW)
			alt_left_right(c);
	}
}

static long	handle_click(int *error_code)
{
	long	c;

	c = 0;
	rp(NULL)->in_read = 1;
	if (read(STDIN_FILENO, &c, sizeof(long)) == -1)
		*error_code = RL_EINTR;
	rp(NULL)->in_read = 0;
	if (*error_code == RL_NOERROR)
	{
		if (c == CTRL_R && !rp(NULL)->history_search.history_search_mode)
			set_history_search_mode();
		if (now_search_history())
			history_search_start(c);
		if (!now_search_history())
		{
			if (c == CTRL_D && rp(NULL)->len == 0)
				return (-1);
			if (c == LEFT_ARROW || c == RIGHT_ARROW)
				move_cursor(c);
			else
				handle_click_sup(c);
		}
	}
	return (c);
}

static void	read_till_newline(int *user_in_len, int *error_code)
{
	long	c;

	c = 0;
	while (c != '\n' && c != -1 && *error_code == RL_NOERROR)
		c = handle_click(error_code);
	*user_in_len = ft_strlen(rp(NULL)->user_in);
	rp(NULL)->user_in[*user_in_len] = (char)(c == -1 ? 0 : '\n');
	rp(NULL)->user_in[*user_in_len + 1] = 0;
}

/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

char		*readline(char *prompt)
{
	char	*ret_user_in;
	int		user_in_len;
	int		user_in_lines;
	int		error_code;

	gayprompt(prompt);
	reset_rp_to_start(prompt);
	error_code = RL_NOERROR;
	read_till_newline(&user_in_len, &error_code);
	user_in_lines = str_n(rp(NULL)->prompt_len) - rp(NULL)->cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "\n", 1);
	if (error_code == RL_NOERROR)
	{
		if (!(ret_user_in = ft_strdup(rp(NULL)->user_in)))
			reset_exit(1);
	}
	else
		ret_user_in = NULL;
	ft_memdel((void **)&(rp(NULL)->prompt));
	ft_memdel((void **)&(rp(NULL)->user_in));
	rp(NULL)->in_readline = 0;
	tc_clear_till_end();
	return (ret_user_in);
}
