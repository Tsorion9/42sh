/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:16:51 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 20:16:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "static_env.h"

void	repl(int tty_input)
{
	t_deque		*command;

	(void)tty_input;
	command = NULL;
	if (isatty(STDIN_FILENO))
	{
		rp(init_rp());
		load_on_file_history(rp(NULL)->history);
	}
	while (1)
	{
		command = parser();
		exec_cmd(command);
	}
	save_in_file_history(rp(NULL)->history);
	if (isatty(STDIN_FILENO))
		free_rp();
}

int		main(int ac, char **av, char **environ)
{
	int	tty_input;

	(void)ac;
	(void)av;
	static_env_action(init, (void *)environ);
	if ((tty_input = isatty(STDIN_FILENO)))
	{
		init_terminal();
		init_prompt();
	}
	set_signal();
	repl(tty_input);
	if (tty_input)
		reset_input_mode();
	static_env_action(del, NULL);
	return (0);
}
