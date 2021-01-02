/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:45:02 by anton             #+#    #+#             */
/*   Updated: 2021/01/02 21:20:56 by nriker           ###   ########.fr       */
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
# include "readline.h"
# include "hashtable.h"

# include "expand.h"

# define CLOSE_STREAM "-"

# define HISTORY_SEARCH_STR_BEFORE "(reverse-i-search)`"
# define HISTORY_SEARCH_STR_NOT_FOUND_BEFORE "(failed reverse-i-search)`"
# define HISTORY_SEARCH_STR_AFTER "': "

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
