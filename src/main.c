#include "21sh.h"

int			ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void		set_term_settings(void)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &g_settings);
	new_settings = g_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	    return_term_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_settings);
}

void        start_program(void)
{
    char *str = readline();
}

int         main(int ac, char **av, char **environ)
{
    char	*termtype;
	char	room_termtype[2048];

	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
	{
		ft_putstr("error\n");
		exit(0);
    }
    (void)ac;
    (void)av;
    set_term_settings();
    start_program();
    return_term_settings();
    return (0);
}
