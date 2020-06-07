#include "21sh.h"

void	expand_user_in(void)
{
	char	tmp[rp()->max_len];

	ft_strcpy(tmp, rp()->user_in);
	free(rp()->user_in);
	rp()->max_len += MIN_CMD_LENGTH;
	if (!(rp()->user_in = (char*)malloc(sizeof(char) * rp()->max_len)))
		reset_exit(1);
	ft_strcpy(rp()->user_in, tmp);
	free(tmp);
}

int		is_print(long c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
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
    else if (is_print(c))
        add_symbol(c);
    else if (c == ALT_LEFT_ARROW || c == ALT_RIGHT_ARROW)
        alt_left_right(c);
    /*else if (c == HOME || c == END) // Необходимо реализовать
        home_end(c); // Проверить!*/
    else if (c == CTRL_LEFT || c == CTRL_RIGHT)
        wordmove_cursor(c);
	else if (c == CTRL_UP || c == CTRL_DOWN)
		strmove_cursor(c);
	else if (c == CTRL_W)
		delete_last_word();
	else if (c == TAB_ARROW)
		completion();
    return (c);
}

void	die(void)
{
	exit(1);
}

static void	read_till_newline(int *user_in_len)
{
    long    c;

	c = 0;
	while (c != '\n')
		c = readline_sup();
	*user_in_len = ft_strlen(rp()->user_in);
	rp()->user_in[*user_in_len] = c;
	rp()->user_in[*user_in_len + 1] = 0;
}

/*
** Позволяет корректно работать со строкой ввода.
** Возвращает строку, введенную пользователем.
*/

char        *readline(char *prompt)
{
    char    *ret_user_in;
    int     user_in_len;
    int     user_in_lines;

	reset_rp_to_start();
	write(STDERR_FILENO, prompt, ft_strlen(prompt));
	read_till_newline(&user_in_len);
	user_in_lines = str_n() - rp()->cur_pos[1];
	while (user_in_lines-- > 0)
		write(STDERR_FILENO, "\n", 1);
    rp()->user_in -= rp()->line_shift;
    rp()->user_in[ft_strlen(rp()->user_in) - 1] = 0;
    write(STDERR_FILENO, "\n", 1);
    if (!(ret_user_in = ft_strdup(rp()->user_in)))
		exit(1);
	free(rp()->user_in);
	//printf("len = %ld, max_len = %ld\n", rp()->len, rp()->max_len);
	add_to_start_history(rp()->history, ret_user_in, user_in_len);
    return (ret_user_in);
}
