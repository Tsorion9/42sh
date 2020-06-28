/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:18:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 23:41:02 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int				ft_putint(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

struct termios	*set_input_mode(int param)
{
	struct termios			new_settings;
	static struct termios	g_saved_attribute;

	if (param)
	{
		tcgetattr(STDIN_FILENO, &g_saved_attribute);
		new_settings = g_saved_attribute;
		new_settings.c_lflag &= ~ICANON;
		new_settings.c_lflag &= ~ECHO;
		new_settings.c_cc[VTIME] = 0;
		new_settings.c_cc[VMIN] = 1;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_settings);
		return (NULL);
	}
	else
		return (&g_saved_attribute);
}

void			reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, set_input_mode(0));
}

void			set_canon_input_mode(int reset)
{
	struct termios			new_settings;
	static struct termios	g_saved_attribute;

	if (!isatty(0))
		return ;
	if (reset)
	{
		tcgetattr(STDIN_FILENO, &g_saved_attribute);
		new_settings = g_saved_attribute;
		new_settings.c_lflag |= ICANON;
		new_settings.c_lflag |= ECHO;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_settings);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_attribute);
}

void			init_terminal(void)
{
	char	*termtype;

	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(NULL, termtype) != 1)
	{
		ft_putstr_fd("Terminal initialisation error\n", STDERR_FILENO);
		exit(1);
	}
	set_input_mode(1);
}
