#include "21sh.h"

int			ft_putint(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void		set_input_mode()
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &g_saved_attribute);
	new_settings = g_saved_attribute;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	    reset_input_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_attribute);
}

void		test_tokenizing(char *user_in)
{
	TOKEN	token;
	char	token_type_name[13][BUFFSIZE] = {"NUMBER", "WORD",\
	"GREATER", "LESS", "GREATER_GREATER", "LESS_LESS",\
	"GREATER_AND", "LESS_AND", "AND_GREATER", "ASSIGNMENT_WORD",\
	"PIPE", "LINE_SEPARATOR", "END_LINE"};

	while (1)
	{
		token = get_next_token(user_in);
		if (token.token_type == WORD || token.token_type == NUMBER)
			printf("%s : %s\n", token_type_name[token.token_type], token.attribute);
		else
			printf("%s\n", token_type_name[token.token_type]);
		if (token.token_type == END_LINE)
			break ;
	}
}

void		back_to_start_history(void)
{
	if (g_history)
		while (g_history->prev)
			g_history = g_history->prev;
}

void		reset_cur_pos(void)
{
	g_cur_pos[0] = 3;
	g_cur_pos[1] = 1;
}

void		reset_readline_to_start_position(void)
{
	back_to_start_history();
	reset_cur_pos();
	g_user_in[0] = 0;
	g_line_shift = 0;
	g_flag = 0;
}

void        start_program(char **env, int tty_input)
{
	char		*user_in;

	g_history = create_history("");
	load_on_file_history(g_history);
	g_user_in = (char*)malloc(sizeof(char) * BUFFSIZE);
	reset_readline_to_start_position();
	if (tty_input)
		write(STDERR_FILENO, "$>", 2);
    user_in = readline(tty_input);
	while (ft_strcmp(user_in, "exit") != 0)
	{
		reset_readline_to_start_position();
		user_in = expansion(user_in, env);
		add_to_start_history(g_history, user_in);
		free(user_in);
		if (tty_input)
			write(STDERR_FILENO, "$>", 2);
		user_in = readline(tty_input);
	}
	free(user_in);
	save_in_file_history(g_history);
	free_history_list(g_history);
}

void		init_terminal()
{
    char			*termtype;

	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(NULL, termtype) != 1)
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		exit(1);
    }
    set_input_mode();
}

int			ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (a == 0)
		return (w.ws_col);
	return (w.ws_row);
}

void		signal_processing(int signal_code)
{
	size_t	user_in_lines;

	if (signal_code == SIGINT)
	{
		write(STDERR_FILENO, "^C", 2);
		user_in_lines = str_n(g_user_in) + 2 - g_cur_pos[1];
		while (user_in_lines-- > 0)
			write(STDERR_FILENO, "\n", 1);
		g_user_in -= g_line_shift;
		write(STDERR_FILENO, "$>", 2);
		reset_readline_to_start_position();
	}
}

void		set_signal(void)
{
	signal(SIGINT, signal_processing);
}

int         main(int ac, char **av, char **environ)
{
	int				tty_input;

    (void)ac;
    (void)av;
	tty_input = 0; /* Valgrind says it is uninitialized otherwise. Why? */
	if ((tty_input = isatty(STDIN_FILENO)))
		init_terminal();
	set_signal();
    start_program(environ, tty_input);
	if (tty_input)
		reset_input_mode();
    return (0);
}
