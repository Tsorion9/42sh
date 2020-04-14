#include "21sh.h"

/*
** Проверяет, является ли '\', с индексом start_check, цитированием
*/

int         check_backslash(char *user_in, int start_check)
{
    int res;

    if (start_check < 0)
        return (1);
    res = 1;
    while (user_in[start_check] == '\\' && start_check >= 0)
    {
        res++;
        start_check--;
    }
    return (res % 2);
}

/*
** Проверяет необходимость перевода на новую строку
*/

static void check_flag(char *user_in, char *flag)
{
    int i;

    i = 0;
    while (user_in[i] != 0)
    {
        if (user_in[i] == *flag  && *flag == '\'')
            *flag = 0;
        else if (user_in[i] == '\"' && user_in[i] == *flag\
            && check_backslash(user_in, i - 1) == 1)
            *flag = 0;
        else if ((user_in[i] == '\'' || user_in[i] == '\"') && *flag == 0\
            && check_backslash(user_in, i - 1) == 1)
            *flag = user_in[i];
        i++;
    }
}

int         str_n(char *user_in)
{
    int n;

    n = 0;
    while (*user_in != 0)
    {
        if (*user_in == '\n')
            n++;
        user_in++;
    }
    return (n);
}

/*
** Чистит все строки, введенные пользователем.
*/

void        clear_all_line(void)
{
    int n;

    if (ft_strchr(rp()->user_in, '\n') == NULL)
    {
        clear_line(3);
        rp()->cur_pos[0] = 3;
        return ;
    }
    n = str_n(rp()->user_in) + 1;
    while (rp()->cur_pos[1] != n)
        tc_cursor_down();
    while (rp()->cur_pos[1] > 1)
    {
        clear_line(0);
        tc_cursor_up();
    }
    tc_cursor_right();
    tc_cursor_right();
    tc_clear_till_end();
}

void        cur_pos_after_putstr(int *cur_pos)
{
    int i;
    int n;

    cur_pos[1] = str_n(rp()->user_in) + 1;
    if (ft_strchr(rp()->user_in, '\n') == NULL)
        cur_pos[0] = ft_strlen(rp()->user_in) + 3;
    else
    {
        cur_pos[0] = 1;
        i = 0;
        n = cur_pos[1] - 1;
        while (n != 0)
        {
            if (rp()->user_in[i] == '\n')
                n--;
            i++;
        }
        while (rp()->user_in[i] != 0)
        {
            cur_pos[0]++;
            i++;
        }
    }
}

void        up_down_arrow_sup(void)
{
    clear_all_line();
    ft_strcpy(rp()->user_in, rp()->history->str);
    ft_putstr(rp()->user_in);
    cur_pos_after_putstr(rp()->cur_pos);
}

void        up_down_arrow(long c)
{
    if (ft_strcmp(rp()->user_in, rp()->history->str) != 0)
    {
        free(rp()->history->str);
        rp()->history->str = ft_strdup(rp()->user_in);
    }
    if (c == UP_ARROW && rp()->history->next != NULL)
    {
        rp()->history = rp()->history->next;
        up_down_arrow_sup();
    }
    else if (c == DOWN_ARROW && rp()->history->prev != NULL)
    {
        rp()->history = rp()->history->prev;
        up_down_arrow_sup();
    }
}

#ifdef DEBUG_INPUT_CHARS
#include <stdio.h>
#endif
static long readline_sup(void)
{
    long    c;

    c = 0;
    read(STDIN_FILENO, &c, sizeof(long));
	#ifdef DEBUG_INPUT_CHARS
	printf("%ld\n", c); // Compile with -DDEBUG_INPUT_CHARS
	fflush(stdout);		// To enable this part of code
	#endif
    if (c == LEFT_ARROW || c == RIGHT_ARROW)
        move_cursor(c);
    else if (c == UP_ARROW || c == DOWN_ARROW)
        up_down_arrow(c);
    else if (c == BACKSPACE)
        delete_symbol();
    else if (c == DEL)
        delete_symbol_forward();
    else if (c >= ' ' && c <= '~') // Probably, ft_isprint() here?
        insert_symbol(c);
    else if (c == ALT_LEFT_ARROW || c == ALT_RIGHT_ARROW)
        alt_left_right(c); // Проверить!
    else if (c == HOME || c == END)
        home_end(c); // Проверить!
    else if (c == CTRL_LEFT || c == CTRL_RIGHT)
        wordmove_cursor(c);
	else if (c == CTRL_W)
		delete_last_word();
    return (c);
}

void	die(void)
{
	exit(1);
}

void	read_till_newline(int *user_in_len, \
		int tty)
{
	char	*nl;
    long    c;

	c = 0;
	if (tty)
	{
		while (c != '\n')
			c = readline_sup();
		*user_in_len = ft_strlen(rp()->user_in);
		rp()->user_in[*user_in_len] = c;
		rp()->user_in[*user_in_len + 1] = 0;
	}
	else
	{
		nl = 0;
		c = get_next_line(STDIN_FILENO, &nl);
		if (c == -1)
			die();
		rp()->user_in[0] = 0;
		if (nl)
			ft_strncpy(rp()->user_in, nl, MAX_CMD_LENGTH - 2);
		rp()->user_in[MAX_CMD_LENGTH - 1] = 0;
		if ((*user_in_len = ft_strlen(nl)) > MAX_CMD_LENGTH - 1)
			die();
		free(nl);
	}
}

/*
** Пероводит на новую строку и позволяет продолжить ввод
** для пользователя в случае, если цитирование не закрыто
*/

static void quoting(int tty)
{
    int     user_in_len;
    int     user_in_lines;

    rp()->cur_pos[0] = START_COL_POS;
    rp()->cur_pos[1] = START_ROW_POS;
	if (tty)
	{
        write(STDERR_FILENO, "\n", 1);
		write(STDERR_FILENO, "> ", 2);
	}
	read_till_newline(&user_in_len, tty);
	user_in_lines = str_n(rp()->user_in) - rp()->cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
	check_flag(rp()->user_in, &(rp()->flag));
    if (rp()->flag != 0 || check_backslash(rp()->user_in, user_in_len - 1) == 0)
    {
        rp()->line_shift += user_in_len + 1;
        rp()->user_in += user_in_len + 1;
        quoting(tty);
    }
}


/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

char        *readline(int tty_input)
{
    char    *ret_user_in;
    int     user_in_len;
    int     user_in_lines;

	read_till_newline(&user_in_len, tty_input);
	user_in_lines = str_n(rp()->user_in) - rp()->cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
	check_flag(rp()->user_in, &(rp()->flag));
    if (rp()->flag != 0 || check_backslash(rp()->user_in, user_in_len - 1) == 0)
    {
        rp()->line_shift += user_in_len + 1;
        rp()->user_in += user_in_len + 1;
        quoting(tty_input);
    }
    rp()->user_in -= rp()->line_shift;
    rp()->user_in[ft_strlen(rp()->user_in) - 1] = 0;
    write(STDERR_FILENO, "\n", 1);
    if (!(ret_user_in = ft_strdup(rp()->user_in)))
        exit(1);
    return (ret_user_in);
}
