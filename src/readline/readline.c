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

void        clear_all_line(char *user_in, int *cur_pos)
{
    int n;

    if (ft_strchr(user_in, '\n') == NULL)
    {
        clear_line(*cur_pos, 3);
        cur_pos[0] = 3;
        return ;
    }
    n = str_n(user_in) + 1;
    while (cur_pos[1] != n)
        tc_cursor_down(cur_pos);
    while (cur_pos[1] > 1)
    {
        clear_line(cur_pos[0], 0);
        tc_cursor_up(cur_pos);
    }
    tc_cursor_right(cur_pos);
    tc_cursor_right(cur_pos);
    tc_clear_till_end();
}

void        cur_pos_after_putstr(char *user_in, int *cur_pos)
{
    int i;
    int n;

    cur_pos[1] = str_n(user_in) + 1;
    if (ft_strchr(user_in, '\n') == NULL)
        cur_pos[0] = ft_strlen(user_in) + 3;
    else
    {
        cur_pos[0] = 1;
        i = 0;
        n = cur_pos[1] - 1;
        while (n != 0)
        {
            if (user_in[i] == '\n')
                n--;
            i++;
        }
        while (user_in[i] != 0)
        {
            cur_pos[0]++;
            i++;
        }
    }
}

void        up_down_arrow_sup(char *user_in, int *cur_pos, t_history **history)
{
    clear_all_line(user_in, cur_pos);
    ft_strcpy(user_in, (*history)->str);
    ft_putstr(user_in);
    cur_pos_after_putstr(user_in, cur_pos);
}

void        up_down_arrow(char *user_in, int *cur_pos, t_history **history, long c)
{
    if (ft_strcmp(user_in, (*history)->str) != 0)
    {
        free((*history)->str);
        (*history)->str = ft_strdup(user_in);
    }
    if (c == UP_ARROW && (*history)->next != NULL)
    {
        *history = (*history)->next;
        up_down_arrow_sup(user_in, cur_pos, history);
    }
    else if (c == DOWN_ARROW && (*history)->prev != NULL)
    {
        *history = (*history)->prev;
        up_down_arrow_sup(user_in, cur_pos, history);
    }
}

#ifdef DEBUG_INPUT_CHARS
#include <stdio.h>
#endif
static long readline_sup(char *user_in, int *cur_pos, t_history **history)
{
    long    c;

    c = 0;
    read(STDIN_FILENO, &c, sizeof(long));
	#ifdef DEBUG_INPUT_CHARS
	printf("%ld\n", c); // Compile with -DDEBUG_INPUT_CHARS
	fflush(stdout);		// To enable this part of code
	#endif
    if (c == LEFT_ARROW || c == RIGHT_ARROW)
        move_cursor(c, cur_pos, user_in);
    else if (c == UP_ARROW || c == DOWN_ARROW)
        up_down_arrow(user_in, cur_pos, history, c);
    else if (c == BACKSPACE)
        delete_symbol(user_in, cur_pos);
    else if (c == DEL)
        delete_symbol_forward(user_in, cur_pos);
    else if (c >= ' ' && c <= '~') // Probably, ft_isprint() here?
        insert_symbol(user_in, cur_pos, c);
    else if (c == ALT_LEFT_ARROW || c == ALT_RIGHT_ARROW)
        alt_left_right(c, cur_pos, user_in); // Проверить!
    else if (c == HOME || c == END)
        home_end(c, cur_pos, user_in); // Проверить!
    else if (c == CTRL_LEFT || c == CTRL_RIGHT)
        wordmove_cursor(c, cur_pos, user_in);
	else if (c == CTRL_W)
		delete_last_word(user_in, cur_pos);
    return (c);
}

void	die(void)
{
	exit(1);
}

void	read_till_newline(int *cur_pos, int *user_in_len, \
		int tty, char *user_in, t_history *history)
{
	char	*nl;
    long    c;

	c = 0;
	if (tty)
	{
		while (c != '\n')
			c = readline_sup(user_in, cur_pos, &history);
		*user_in_len = ft_strlen(user_in);
		user_in[*user_in_len] = c;
		user_in[*user_in_len + 1] = 0;
	}
	else
	{
		nl = 0;
		c = get_next_line(STDIN_FILENO, &nl);
		if (c == -1)
			die();
		*user_in = 0;
		if (nl)
			ft_strncpy(user_in, nl, BUFFSIZE - 2);
		user_in[BUFFSIZE - 1] = 0;
		if ((*user_in_len = ft_strlen(nl)) > BUFFSIZE - 1)
			die();
		free(nl);
	}
}


/*
** Пероводит на новую строку и позволяет продолжить ввод
** для пользователя в случае, если цитирование не закрыто
*/

static void quoting(char *user_in, char flag, int tty, t_history *history)
{
    int     user_in_len;
    int     cur_pos[2];

    cur_pos[0] = 3;
    cur_pos[1] = 1;
	if (tty)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, "> ", 2);
	}
	read_till_newline(cur_pos, &user_in_len, tty, user_in, history);
	check_flag(user_in, &flag);
    if (flag != 0 || check_backslash(user_in, user_in_len - 1) == 0)
        quoting(user_in + user_in_len + 1, flag, tty, history);
}

/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

char        *readline(int tty_input, t_history *history)
{
    char    user_in[BUFFSIZE];
    char    flag;
    int     cur_pos[2];
    int     user_in_len;

    user_in[0] = 0;
    cur_pos[0] = 3;
    cur_pos[1] = 1;
    flag = 0;
	user_in_len = 0;
	if (tty_input)
		write(STDOUT_FILENO, "$>", 2);
	read_till_newline(cur_pos, &user_in_len, tty_input, user_in, history);
	check_flag(user_in, &flag);
    if (flag != 0 || check_backslash(user_in, user_in_len - 1) == 0)
        quoting(user_in + user_in_len + 1, flag, tty_input, history);
    return (ft_strdup(user_in));
}
