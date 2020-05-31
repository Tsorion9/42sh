#ifndef LEX_H
#define LEX_H

#include "21sh.h"


char 		*quoting(void);
void		close_quote(char **user_in);
void	read_till_newline(int *user_in_len, \
		int tty);
t_token		get_token_number(char *user_in, int *index, char *buf,\
    int *buf_index, int prev_token);
t_token	get_token_and_greater(char *user_in, int *index, char *buf,\
    int *buf_index);
t_token		get_token_pipe(int *index);
t_token		get_token_end_line(int *index);
t_token		get_toket_line_separator(int *index);
t_token		get_token_word(char **user_in, int *index, char *buf,\
    int *buf_index);
t_token		write_singe_quotes_to_buf(char **user_in, int *index, char *buf,\
    int *buf_index);
t_token		write_double_quotes_to_buf(char **user_in, int *index, char *buf,\
    int *buf_index);
t_token		get_token_less(char *user_in, int *index);
t_token		get_token_greater(char *user_in, int *index);
char		*create_attribute(char *buf, int buf_index);
bool		is_ws(char c);
#endif
