#include "21sh.h"

/*
** Удаляет символ и печатает строку
*/

void        delete_symbol(char *user_in, int *cur_pos)
{
    int     len;
    int     i;

    if (*cur_pos == 3)
        return ;
    len = ft_strlen(user_in);
    i = 0;
    while (i < *cur_pos - 4)
        i++;
    while (i < len - 1)
    {
        user_in[i] = user_in[i + 1];
        i++;
    }
    user_in[i] = 0;
    clear_line(*cur_pos);
    ft_putstr(user_in);
    while (len + 3 > *cur_pos)
    {
		tc_cursor_left(NULL);
        len--;
    }
    (*cur_pos)--;
}

void		delete_symbol_forward(char *user_in, int *cur_pos)
{
	if (!inside_boundaries(*cur_pos + 1, user_in))
		return ;
	tc_cursor_right(cur_pos);
	delete_symbol(user_in, cur_pos);
}

void        delete_last_word(char *user_in, int *cur_pos)
{
	while (ft_isspace(*input_under_cursor(*cur_pos, user_in)) &&\
			inside_boundaries(*cur_pos - 1, user_in))
		delete_symbol(user_in, cur_pos);
	while (!ft_isspace(*input_under_cursor(*cur_pos, user_in)) &&\
			inside_boundaries(*cur_pos - 1, user_in))
		delete_symbol(user_in, cur_pos);
}

/*
** Добавляет символ и печатает строку
*/

void        insert_symbol(char *user_in, int *cur_pos, char c)
{
    int     len;
    char    *str;
    int     i;

    i = 0;
    while (i < *cur_pos - 3)
        i++;
    str = ft_strdup(user_in + i);
    ft_strcpy(user_in + i + 1, str);
    free(str);
    user_in[i] = c;
    clear_line(*cur_pos);
    ft_putstr(user_in);
    len = ft_strlen(user_in);
    while (len + 2 > *cur_pos)
    {
		tc_cursor_left(NULL);
        len--;
    }
    (*cur_pos)++;
}
