/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:45:02 by anton             #+#    #+#             */
/*   Updated: 2020/12/29 21:57:39 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC21SH_H
# define INC21SH_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include "parser.h"
# include "heredoc.h"
# include "exec.h"
# include <dirent.h>

# include "expand.h"


# define CLOSE_STREAM "-"

# define HISTORY_SEARCH_STR_BEFORE "(reverse-i-search)`"
# define HISTORY_SEARCH_STR_NOT_FOUND_BEFORE "(failed reverse-i-search)`"
# define HISTORY_SEARCH_STR_AFTER "': "

# define COM_CMD 1
# define COM_VAR 2
# define COM_FILE 3
# define COM_VAR_WORD_BRACE 4
# define COM_VAR_WORD_DOLLAR 5

# define TRUE 1
# define FALSE 0

# define GETCURSORPOS "\e[6n"

# include "command.h"
# include "deque.h"

int						last_cmd_status(int need_update, int new_value);
void					set_canon_input_mode(int reset);
void					set_signal(void);
int						have_children_global_request(int set_value, int value);
int						fuck_checklist_signal_state(int need_update,\
		int new_value);
char					*get_prompt(int which);

typedef struct			s_str
{
	char				*buf;
	size_t				len;
	size_t				max_len;
	size_t				index;
}						t_str;

typedef struct			s_completion
{
	char				*str;
	struct s_completion	*next;
	int					com_type;
}						t_completion;

typedef struct			s_history
{
	char				*str;
	size_t				len;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_history_search
{
	char				str[BUFFSIZE];
	size_t				len;
	size_t				index;
	int					history_search_mode;
}						t_history_search;

typedef struct			s_column
{
	int			col;
	int			row;
	int			buf_size;
	int			max_width;
	int			width_column;
	int			col_got;
	int			row_got;
}						t_column;

/*
** @user_in	buffer (heap)
** @len	length of user input
** @max_len	current size of buffer
** @cur_pos	offset sursor from start of prompt (0 = cols, 1 =
** rows) count from 1
** @history	position in history
** @ws_col	window size columns
** @ws_row	window size rows
** @prompt_len	length of the prompt + 1 == start position of cursor
*/

typedef struct			s_rp
{
	char				*prompt;
	char				*user_in;
	size_t				len;
	size_t				max_len;
	size_t				index;
	int					cur_pos[2];
	t_history			*history;
	unsigned short		ws_col;
	unsigned short		ws_row;
	size_t				prompt_len;
	int					in_readline;
	int					in_read;
	t_history_search	history_search;
	int					prev_pos_curs;
	int					column_end_of_line;
	int					competitions_raws;
}						t_rp;

/*
** TOKEN
*/

typedef struct			s_token
{
	int					token_type;
	char				*attribute;
}						t_token;

# define TOKEN t_token

/*
** Defines for token
*/

# define NUMBER 0
# define WORD 1
# define ASSIGNMENT_WORD 9
# define PIPE 10
# define LINE_SEPARATOR 11
# define END_LINE 12

/*
** REDIRECTION
** '>' '<' '>>' '<<' '>&' '<&' '&>'
*/

# define GREATER 2
# define LESS 3
# define GREATER_GREATER 4
# define LESS_LESS 5
# define GREATER_AND 6
# define LESS_AND 7
# define AND_GREATOR 8


# define PROMPT_LEN 2

void					init_terminal(void);
struct termios			*set_input_mode(int a);
void					set_signal(void);
void					reset_input_mode(void);
void					strmove_cursor(long c);
int						is_print(long c);
int						executable_file(char *file_name, char *path);
void					free_rp(void);
void					free_history_list(t_history *history);
int						find_complection_pos(char *line, int i);
int						is_valid_name(char *str);
int						is_valid_name_char(char c);
t_str					*init_str(void);
void					expand_str(t_str *str);
void					free_str(t_str *str);
void					tc_save_cursor_pos(void);
void					tc_restore_saved_cursor_pos(void);
void					history_search_start(long c);
void					add_symbol_in_str(char *str, char symbol, size_t symbol_index);
void					delete_symbol_in_str(char *str, size_t symbol_index);
void					set_new_user_in(const char *str);
void					save_user_in_history(void);
void					set_history_search_mode(void);
int						now_search_history(void);
int						get_cursor_position(void);
void					readline_putstr(const char *s, int *cur_pos, size_t prompt_len);

/*
** Complection
*/

void					completion(void);
char					*tab_cut_word(char *user_in, int i);
int						tab_check_space(char *user_in, int i);
void					add_new_completion(t_completion **com_lst, char *str);
void					free_completion(t_completion *com_lst, \
						t_completion *matches, char *remaider_word, char *path);
t_completion			*add_files_path_env(void);
char					*return_path(char *remaider_word);
void					complete_word(t_completion *matches,\
						char *remaider_word, char *path);
t_completion			*ret_possible_matches(char *path, int first_word);
char					*cut_word(char cut_symbol, int i);
t_completion			*ret_matches(t_completion *com_lst, char **str_search);
char					*ft_strcut(const char *s, int c);

/*
** Complection API for vars
*/

t_completion			*ret_possible_vars(void);
char					*cut_uncut_remainder_word(char *remainder_word);
char					*cut_uncut_remainder_word_dol(char *remainder_word);
void					com_api_print_var_suggestion(t_completion *matches, char *remainder_word,
								char *path);
void					com_api_print_normal_var_suggestions(t_completion *matches);
void					com_api_print_many_var_suggestions(t_completion *matches);
int						check_var_word_brace(char *line, int i);
int						check_brace_in_var_word(char *line, int i);
int						check_var_word_dollar(char *line, int i);
void					change_full_word_var_word_dollar(char *full_word);
void					change_full_word_var_word_brace(char *full_word);

/*
** Complection API for print possibilities
*/

void					com_api_move_curs_to_end_line(void);
void					com_api_move_curs_to_prev_pos(void);
void					com_api_return_curs_to_line(void);
void					com_api_return_curs_to_position(int columns_right);
void					com_api_print_lst(t_completion *matches);
void					com_api_print_suggestion(t_completion *matches, char *remainder_word,
								char *path);
void					com_api_clear_till_end(void);
void					create_t_column(t_column **cl);
int						com_api_get_curs_col(void);
int						com_api_get_curs_row(void);
int						complections_list_len(t_completion *matches);
void					com_api_print_many_suggestions(t_completion *matches);
void					com_api_print_normal_suggestions(t_completion *matches);
int						check_big_list(int quantity_possibilities);
void					get_size_of_columns(char **buf, t_column *cl);
void					print_column(char **buf, t_column *cl);

/*
** Interface for lexer
*/

t_token					*lex(void);

# define PARSER_FAILURE 0
# define PARSER_SUCCESS 1

/*
** Lexer should also recognize theese guys
** Clobber '>|'
** Bang '!'
** dlessash <<-
*/

# define CLOBBER -9
# define BANG -10
# define DLESSDASH -11

typedef enum			e_token_type
{
	eof = -1,
	number = NUMBER,
	word = WORD,
	ass_word = ASSIGNMENT_WORD,
	pipel = PIPE,
	sep = LINE_SEPARATOR,
	__newline = END_LINE,
	greater = GREATER,
	less = LESS,
	dgreat = GREATER_GREATER,
	dless = LESS_LESS,
	dlessash = DLESSDASH,
	clobber = CLOBBER,
	bang = BANG,
	lessand = LESS_AND,
	gr_and = GREATER_AND,
	signal_token
}						t_token_type;

/*
** Complete command is a deque of pipelines (t_pipeline)
** t_pipeline->commands is a deque of simple commands (t_simple_cmd)
** Simple command t_simple_cmd is 2 deques of words and redirections
** (wl, arl)
** arl is a deque of type t_ar
*/

typedef struct			s_pipeline
{
	t_deque				*commands;
	int					bang;
}						t_pipeline;

typedef struct			s_simple_cmd
{
	t_deque				*wl;
	t_deque				*arl;
}						t_simple_cmd;

typedef enum			e_ar
{
	assignment,
	redirection
}						t_ear;

typedef struct			s_ar
{
	void				*data;
	t_ear				what;
}						t_ar;

typedef struct			s_io_redir
{
	int					fd;
	t_token_type		operation;
	t_list				*where;
}						t_io_redir;

/*
** Parser's internal token buffer. Needed for backtracking
** Equivalrnt to getc() ungetc()
*/

void					ungett(t_deque **tokbuf_g, t_deque **tokbuf_l);
t_token					*gett(t_deque **tokbuf_g, t_deque **tokbuf_l);
void					erase_tokbuf(t_deque **tokbuf);
void					flush_tokbuf(t_deque **tokbuf_g, t_deque **tokbubf_l);
void					syntax_error(t_token *token);
void					add_ar(t_simple_cmd **cmd, void *data, t_ear what);

/*
** Nonterminal recursive procedures
*/

int						match_complete_command(t_deque **command,\
						t_deque **tokbuf_g);
int						match_list(t_deque **command, t_deque **tokbuf_g);
int						match_list_dash(t_deque **command, t_deque **tokbuf_g);
int						match_pipeline(t_deque **command, t_deque **tokbuf_g);
int						match_pipe_sequence(t_pipeline *pipeline,\
						t_deque **tokbuf_g);
int						match_simple_command(t_simple_cmd **cmd,\
						t_deque **tokbubf_g);
void					match_linebreak(t_deque **tokbubf_g,\
						t_deque **tokbubf_l);
int						match_cmd_suffix(t_simple_cmd **cmd,\
						t_deque **tokbubf_g);
int						match_cmd_prefix(t_simple_cmd **cmd,\
						t_deque **tokbubf_g);
int						match_io_redirect(t_simple_cmd *cmd,\
						t_deque **tokbubf_g);
int						match_io_file(t_io_redir *redir, t_deque **tokbubf_g);
int						match_io_here(t_io_redir *redir, t_deque **tokbubf_g);

/*
** DEBUG; Do not use in project!
*/

void					print_cmd_dbg(t_deque *command);
void					rm_compl_cmd(t_deque **command);
void					rm_pipeline(void *pipeline);
void					rm_simple_cmd(void *command);
void					rm_ar(void *p);
void					rm_redir(t_io_redir *redir);
void					del_inside_wl(void *content, size_t content_size);

void					*del_array(char **env);

t_deque					*parser(void);

void					reset_exit(int status);

/*
** Expand.h
*/

typedef enum			e_exp_state
{
	norm,
	in_sqt,
	in_dqt
}						t_exp_state;

int						expand_dollar(char **word, int *pos);
char					*expand(char *s);
void					expand_tilda(char **s, int *pos);
void					expand_pipeline(void *pipeline);
void					expand_complete_cmd(t_deque *cmd);

/*
** Syntax error
*/

# define SYNTAX_ERROR_STATE_GET 1
# define SYNTAX_ERROR_STATE_SET 0
# define SYNTAX_ERROR_STATE_OK 0
# define SYNTAX_ERROR_STATE_NOT_OK 1

int						syntax_error_state_action(int request, int param);

void					init_prompt(void);

#endif
