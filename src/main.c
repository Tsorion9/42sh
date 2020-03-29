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

void		test_tokenizing(char *user_in)
{
	TOKEN	token;
	char	token_type_name[13][BUFFSIZE] = {"NUMBER", "WORD",\
	"GREATER", "LESS", "GREATER_GREATER", "LESS_LESS",\
	"GREATER_AND", "LESS_AND", "AND_GREATER", "ASSIGNMENT_WORD",\
	"PIPE", "LINE_SEPARATOR", "END_LINE"};

	//printf("user_in line = %ld\n", ft_strlen(user_in));
	while (1)
	{
		token = get_next_token(user_in);
		if (token.token_type == WORD)
			printf("%s : %s\n", token_type_name[token.token_type], token.attrinute);
		else
			printf("%s\n", token_type_name[token.token_type]);
		if (token.token_type == END_LINE)
			break ;
	}
}

void        start_program(char **env, int tty_input)
{
	t_history	*history;

	history = NULL;
	history = create_history("");
    char *str = readline(tty_input, history);
	while (ft_strcmp(str, "exit\n") != 0)
	{
		write(STDIN_FILENO, "\n", 1);
		str = expansion(str, env);
		//ft_putstr(str);
		str[ft_strlen(str) - 1] = 0;
		test_tokenizing(str);
		add_to_start(&history, str);
		free(str);
		str = readline(tty_input, history);
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

int			ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (a == 0)
		return (w.ws_col);
	return (w.ws_row);
}

void		signal_processing(int a)
{
	if (a == SIGWINCH)
	{
		
	}
}

void		set_signal(void)
{
	signal(SIGWINCH, signal_processing);
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
