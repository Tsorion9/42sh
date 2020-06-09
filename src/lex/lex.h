#ifndef LEX_H
#define LEX_H

#include "21sh.h"

typedef struct	s_attribute
{
	char	*buf;
	size_t	len;
	size_t	max_len;
	size_t	index;
}				t_attribute;

t_attribute		*init_attribute(void);
void			expand_attr(t_attribute *attr);
void			free_attribute(t_attribute *attr);
char 			*quoting(void);
void			close_quote(char **user_in);
void			read_till_newline(int *user_in_len, \
				int tty);
t_token			get_token_number(char **user_in, int *index, t_attribute *attr, \
				int prev_token);
t_token			get_token_and_greater(char **user_in, int *index, t_attribute *attr);
t_token			get_token_pipe(int *index);
t_token			get_token_end_line(int *index);
t_token			get_toket_line_separator(int *index);
t_token			get_token_word(char **user_in, int *index, t_attribute *attr);
t_token       	write_singe_quotes_to_buf(char **user_in, int *index, t_attribute *attr);
t_token       	write_double_quotes_to_buf(char **user_in, int *index, t_attribute *attr);
t_token			get_token_less(char *user_in, int *index);
t_token			get_token_greater(char *user_in, int *index);
char			*create_attribute(t_attribute *attr);
bool			is_ws(char c);
void			write_char_to_buf(char *user_in, int *index, t_attribute *attr);
bool        	is_digit(char c);
bool        	is_letter(char c);
#endif
