#include "21sh.h"

int			ft_putint(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void		set_input_mode()
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &saved_attribute);
	new_settings = saved_attribute;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void	    reset_input_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attribute);
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

void        start_program(char **env, int tty_input)
{
	t_history	*history;
	char		*user_in;

	history = create_history("");
	load_on_file_history(history);
    user_in = readline(tty_input, history);
	while (ft_strcmp(user_in, "exit") != 0)
	{
		user_in = expansion(user_in, env);
		add_to_start_history(history, user_in);
		free(user_in);
		user_in = readline(tty_input, history);
	}
	free(user_in);
	save_in_file_history(history);
	free_history_list(history);
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
	if (signal_code == SIGINT)
	{
		write(STDERR_FILENO, "^C", 2);
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
