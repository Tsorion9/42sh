/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:45:02 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 16:25:13 by anton            ###   ########.fr       */
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
# include <term.h>
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

# define MIN_CMD_LENGTH 4096
# define BUFFSIZE 4096
# define HISTSIZE 1000

# define PS1 0
# define PS2 1

# define CLOSE_STREAM "-"
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
}						t_completion;

typedef struct			s_history
{
	char				*str;
	size_t				len;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

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
	char				*user_in;
	size_t				len;
	size_t				max_len;
	int					cur_pos[2];
	t_history			*history;
	unsigned short		ws_col;
	unsigned short		ws_row;
	size_t				prompt_len;
	int					in_readline;
	int					in_read;
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

/*
** Character key constants
*/

# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235

# define UP_ARROW  4283163
# define DOWN_ARROW 4348699

# define TAB_ARROW 9

# if defined(__APPLE__) || defined(__NetBSD__)

#  define ALT_LEFT_ARROW 25115
#  define ALT_RIGHT_ARROW 26139

#  define __S_IREAD S_IRUSR
#  define __S_IWRITE S_IWUSR

# else

#  define ALT_LEFT_ARROW 74986827111195
#  define ALT_RIGHT_ARROW 73887315483419

# endif

# ifdef ANTON_UNUSUAL_LAPTOP
#  define BACKSPACE 8
# else
#  define BACKSPACE 127
# endif

# define DEL 2117294875

# define SHIFT_TAB 5921563
# define CTRL_W 23
# define CTRL_Q 17
# define CTRL_R 18
# define CTRL_LEFT 74995417045787
# define CTRL_RIGHT 73895905418011
# define CTRL_UP 71696882162459
# define CTRL_DOWN 72796393790235

# define HOME 4738843
# define END  4607771

# define CTRL_D 4
# define CTRL_C 3
# define CTRL_S 19
# define CTRL_Z 26
# define CTRL_V 22

# define PROMPT_LEN 2

t_rp					*rp(t_rp *change_rp);
t_rp					*init_rp(void);
void					free_rp(void);
void					back_to_start_history_rp(void);
void					init_terminal();
void					reset_input_mode();
struct termios			*set_input_mode(int a);
int						ft_putint(int c);
void					home_end(long c);
int						str_naa(char *user_in);
void					expand_user_in(void);
t_rp					*rp(t_rp *change_rp);
void					inverse_search_index(int cur_pos[2], int index);
void					reset_rp_to_start(void);
int						ft_putint(int c);
char					*readline(char *prompt);
int						ft_isspace(char c);
void					move_cursor(long c);
void					delete_symbol(void);
void					add_symbol(char c);
void					alt_left_right(long c);
void					delete_last_word(void);
void					wordmove_cursor(long c);
void					delete_symbol_forward(void);
int						str_n(void);
void					clear_all_line(void);
void					cur_pos_after_putstr(int *cur_pos);
int						search_last_cur_pos_in_line(void);
int						search_index(void);
void					ret_cur_to_original_pos(int *prev_cur_pos);
int						ret_winsize(int a);
int						check_slash(char *user_in, int start_check);
char					*expansion(char *user_in, char **env);
t_history				*add_new_history(t_history *history, char *str);
void					add_to_start_history(t_history *history, char *str, \
						size_t len);
t_history				*create_history(char *str, size_t len);
void					load_on_file_history(t_history *history);
void					save_in_file_history(t_history *history);
void					free_readline_position(void);
void					check_flag(char *user_in, char *flag);
void					up_down_arrow(long c);
void					set_signal(void);
void					reset_input_mode(void);
void					strmove_cursor(long c);
void					completion(void);
int						is_print(long c);
int						executable_file(char *file_name, char *path);
void					add_new_completion(t_completion **com_lst, char *str);
void					free_completion(t_completion *com_lst, \
						t_completion *matches, char *remaider_word, char *path);
t_completion			*add_files_path_env(void);
char					*return_path(char *remaider_word);
void					complete_word(t_completion *matches,\
						char *remaider_word, char *path);
t_completion			*ret_possible_matches(char *path, int first_word);
char					*cut_word(char cut_symbol, int i);
t_completion			*ret_matches(t_completion *com_lst, char *str_search);
void					free_rp(void);
void					free_history_list(t_history *history);
t_str					*init_str(void);
void					expand_str(t_str *str);
void					free_str(t_str *str);

/*
** Interface for lexer
*/

t_token					*lex(void);

/*
** Funcions that make termcaps interactions more readable
*/

void					tc_cursor_up(void);
void					tc_cursor_down(void);
void					tc_cursor_left(void);
void					tc_cursor_right(void);
void					tc_clear_till_end(void);
void					tc_cursor_n_right(int n);

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
