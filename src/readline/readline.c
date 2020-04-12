#include "21sh.h"

/*
** Проверяет, является ли '\', с индексом start_check, цитированием
*/

int         check_backslash(char *g_user_in, int start_check)
{
    int res;

    if (start_check < 0)
        return (1);
    res = 1;
    while (g_user_in[start_check] == '\\' && start_check >= 0)
    {
        res++;
        start_check--;
    }
    return (res % 2);
}

/*
** Проверяет необходимость перевода на новую строку
*/

static void check_flag(char *g_user_in, char *flag)
{
    int i;

    i = 0;
    while (g_user_in[i] != 0)
    {
        if (g_user_in[i] == *flag  && *flag == '\'')
            *flag = 0;
        else if (g_user_in[i] == '\"' && g_user_in[i] == *flag\
            && check_backslash(g_user_in, i - 1) == 1)
            *flag = 0;
        else if ((g_user_in[i] == '\'' || g_user_in[i] == '\"') && *flag == 0\
            && check_backslash(g_user_in, i - 1) == 1)
            *flag = g_user_in[i];
        i++;
    }
}

int         str_n(char *g_user_in)
{
    int n;

    n = 0;
    while (*g_user_in != 0)
    {
        if (*g_user_in == '\n')
            n++;
        g_user_in++;
    }
    return (n);
}

/*
** Чистит все строки, введенные пользователем.
*/

void        clear_all_line(char *g_user_in)
{
    int n;

    if (ft_strchr(g_user_in, '\n') == NULL)
    {
        clear_line(3);
        g_cur_pos[0] = 3;
        return ;
    }
    n = str_n(g_user_in) + 1;
    while (g_cur_pos[1] != n)
        tc_cursor_down();
    while (g_cur_pos[1] > 1)
    {
        clear_line(0);
        tc_cursor_up();
    }
    tc_cursor_right();
    tc_cursor_right();
    tc_clear_till_end();
}

void        cur_pos_after_putstr(char *g_user_in, int *cur_pos)
{
    int i;
    int n;

    cur_pos[1] = str_n(g_user_in) + 1;
    if (ft_strchr(g_user_in, '\n') == NULL)
        cur_pos[0] = ft_strlen(g_user_in) + 3;
    else
    {
        cur_pos[0] = 1;
        i = 0;
        n = cur_pos[1] - 1;
        while (n != 0)
        {
            if (g_user_in[i] == '\n')
                n--;
            i++;
        }
        while (g_user_in[i] != 0)
        {
            cur_pos[0]++;
            i++;
        }
    }
}

void        up_down_arrow_sup(char *g_user_in)
{
    clear_all_line(g_user_in);
    ft_strcpy(g_user_in, g_history->str);
    ft_putstr(g_user_in);
    cur_pos_after_putstr(g_user_in, g_cur_pos);
}

void        up_down_arrow(char *g_user_in, long c)
{
    if (ft_strcmp(g_user_in, g_history->str) != 0)
    {
        free(g_history->str);
        g_history->str = ft_strdup(g_user_in);
    }
    if (c == UP_ARROW && g_history->next != NULL)
    {
        g_history = g_history->next;
        up_down_arrow_sup(g_user_in);
    }
    else if (c == DOWN_ARROW && g_history->prev != NULL)
    {
        g_history = g_history->prev;
        up_down_arrow_sup(g_user_in);
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
        move_cursor(c, g_user_in);
    else if (c == UP_ARROW || c == DOWN_ARROW)
        up_down_arrow(g_user_in, c);
    else if (c == BACKSPACE)
        delete_symbol(g_user_in);
    else if (c == DEL)
        delete_symbol_forward(g_user_in);
    else if (c >= ' ' && c <= '~') // Probably, ft_isprint() here?
        insert_symbol(g_user_in, c);
    else if (c == ALT_LEFT_ARROW || c == ALT_RIGHT_ARROW)
        alt_left_right(c, g_user_in); // Проверить!
    else if (c == HOME || c == END)
        home_end(c, g_user_in); // Проверить!
    else if (c == CTRL_LEFT || c == CTRL_RIGHT)
        wordmove_cursor(c, g_user_in);
	else if (c == CTRL_W)
		delete_last_word(g_user_in);
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
		*user_in_len = ft_strlen(g_user_in);
		g_user_in[*user_in_len] = c;
		g_user_in[*user_in_len + 1] = 0;
	}
	else
	{
		nl = 0;
		c = get_next_line(STDIN_FILENO, &nl);
		if (c == -1)
			die();
		*g_user_in = 0;
		if (nl)
			ft_strncpy(g_user_in, nl, BUFFSIZE - 2);
		g_user_in[BUFFSIZE - 1] = 0;
		if ((*user_in_len = ft_strlen(nl)) > BUFFSIZE - 1)
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

    g_cur_pos[0] = START_COL_POS;
    g_cur_pos[1] = START_ROW_POS;
	if (tty)
	{
        write(STDERR_FILENO, "\n", 1);
		write(STDERR_FILENO, "> ", 2);
	}
	read_till_newline(&user_in_len, tty);
	user_in_lines = str_n(g_user_in) - g_cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
	check_flag(g_user_in, &g_flag);
    if (g_flag != 0 || check_backslash(g_user_in, user_in_len - 1) == 0)
    {
        g_line_shift += user_in_len + 1;
        g_user_in += user_in_len + 1;
        quoting(tty);
    }
}


/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

char        *readline(int tty_input)
{
    int     user_in_len;
    int     user_in_lines;

	read_till_newline(&user_in_len, tty_input);
	user_in_lines = str_n(g_user_in) - g_cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
	check_flag(g_user_in, &g_flag);
    if (g_flag != 0 || check_backslash(g_user_in, user_in_len - 1) == 0)
    {
        g_line_shift += user_in_len + 1;
        g_user_in += user_in_len + 1;
        quoting(tty_input);
    }
    g_user_in -= g_line_shift;
    g_user_in[ft_strlen(g_user_in) - 1] = 0;
    write(STDERR_FILENO, "\n", 1);
    return (ft_strdup(g_user_in));
}
