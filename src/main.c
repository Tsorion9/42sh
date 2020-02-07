#include "21sh.h"

int			ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void		set_term_settings(struct termios *old_settings)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, old_settings);
	new_settings = *old_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	    return_term_settings(struct termios *old_settings)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_settings);
}

void        start_program(char **env, int tty_input)
{
    char *str = readline(tty_input);
	while (ft_strcmp(str, "exit\n") != 0)
	{
		write(STDIN_FILENO, "\n", 1);
		str = expansion(str, env);
		ft_putstr(str);
		free(str);
		str = readline(tty_input);
	}
}

void		init_terminal(struct termios *term_settings)
{
    char			*termtype;

	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(NULL, termtype) != 1)
	{
		ft_putstr("error\n");
		exit(1);
    }
    set_term_settings(term_settings);
}

int         main(int ac, char **av, char **environ)
{
	struct termios	term_settings;
	int				tty_input;

    (void)ac;
    (void)av;
	tty_input = 0; /* Valgrind says it is uninitialized otherwise. Why? */
	if ((tty_input = isatty(STDIN_FILENO)))
		init_terminal(&term_settings);
    start_program(environ, tty_input);
	if (tty_input)
		return_term_settings(&term_settings);
    return (0);
}
