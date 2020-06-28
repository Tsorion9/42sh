/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:42 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/28 11:32:05 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "inc21sh.h"

int		global_close_quote_newline_erased(int need_update, int value);
int		global_newline_erased(int need_update, int new_value);
t_token	*ret_token(char **user_in, int *need_new_line, int *index);
void	init_new_user_in(char **user_in, char *extra_line);
void	close_backslash(char **user_in, char flag);
char	*quoting(void);
void	close_quote(char **user_in);
void	read_till_newline(int *user_in_len, \
		int tty);
t_token	get_token_number(char **user_in, int *index, t_str *attr, \
		int prev_token);
t_token	get_token_and_greater(char **user_in, int *index, t_str *attr);
t_token	get_token_pipe(int *index);
t_token	get_token_end_line(int *index);
t_token	get_toket_line_separator(int *index);
t_token	get_token_word(char **user_in, int *index, t_str *attr);
t_token	write_singe_quotes_to_buf(char **user_in, int *index, t_str *attr);
t_token	write_double_quotes_to_buf(char **user_in, int *index, t_str *attr);
t_token	get_token_less(char *user_in, int *index);
t_token	get_token_greater(char *user_in, int *index);
char	*create_attribute(t_str *attr);
int		is_ws(char c);
void	write_char_to_buf(char *user_in, int *index, t_str *attr);
int		is_digit(char c);
int		is_letter(char c);
t_token	*copy_init_token(t_token t);
t_token	*new_eof(void);

#endif
