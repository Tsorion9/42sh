/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:42 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:42 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "21sh.h"

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
bool	is_ws(char c);
void	write_char_to_buf(char *user_in, int *index, t_str *attr);
bool	is_digit(char c);
bool	is_letter(char c);

#endif
