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

/*
** Функция для обработки сигналов.
*/

void		signal_processing(int signal_code)
{
	size_t	user_in_lines;

	if (signal_code == SIGINT)
	{
		write(STDERR_FILENO, "^C", 2);
		user_in_lines = str_n(rp()->user_in) + 2 - rp()->cur_pos[1];
		while (user_in_lines-- > 0)
			write(STDERR_FILENO, "\n", 1);
		rp()->user_in -= rp()->line_shift;
		write(STDERR_FILENO, "$>", 2);
		reset_rp_to_start();
	}
}

void		set_signal(void)
{
	signal(SIGINT, signal_processing);
}

void		back_to_start_history_rp(void)
{
	if (rp()->history)
		while (rp()->history->prev)
			rp()->history = rp()->history->prev;
}

void		reset_cur_pos_rp(void)
{
	rp()->cur_pos[0] = START_COL_POS;
	rp()->cur_pos[1] = START_ROW_POS;
}

void		reset_rp_to_start(void)
{
	back_to_start_history_rp();
	reset_cur_pos_rp();
	rp()->user_in[0] = 0;
	rp()->line_shift = 0;
	rp()->flag = 0;
}

t_rp		*readline_position(t_rp *change_rp)
{
	static t_rp	*rp;

	if (!change_rp)
		return (rp);
	else
		rp = change_rp;
	return (NULL);
}

t_rp		*init_rp(void)
{
	t_rp	*rp;

	if (!(rp = (t_rp*)malloc(sizeof(t_rp))))
		exit(1);
	if (!(rp->user_in = (char*)malloc(sizeof(char) * MAX_CMD_LENGTH)))
		exit(1);
	rp->index = 0;
	rp->cur_pos[0] = START_COL_POS;
	rp->cur_pos[1] = START_ROW_POS;
	rp->flag = 0;
	rp->line_shift = 0;
	rp->history = create_history("");
	return (rp);
}

void        start_program(char **env, int tty_input)
{
	char		*user_in;

	readline_position(init_rp());
	load_on_file_history(rp()->history);
	while (21)
	{
		reset_rp_to_start();
		if (tty_input)
			write(STDERR_FILENO, "$>", 2);
		user_in = readline(tty_input);
		add_to_start_history(rp()->history, user_in);
		if (!(ft_strcmp(user_in, "exit")))
			break ;
		free(user_in);
	}
	free(user_in);
	free(rp()->user_in);
	save_in_file_history(rp()->history);
	free_history_list(rp()->history);
	free(rp());
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
