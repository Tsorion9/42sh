
#ifndef READLINE_H
# define READLINE_H

# include "libft.h"
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include <dirent.h>
# include <sys/stat.h>

# define PS1 0
# define PS2 1

# define MIN_CMD_LENGTH 4096
# define BUFFSIZE 4096
# define HISTSIZE 1000

# define HISTORY_SEARCH_STR_BEFORE "(reverse-i-search)`"
# define HISTORY_SEARCH_STR_NOT_FOUND_BEFORE "(failed reverse-i-search)`"
# define HISTORY_SEARCH_STR_AFTER "': "

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
# define CTRL_E 5
# define CTRL_R 18
# define CTRL_S 19
# define CTRL_Z 26
# define CTRL_V 22

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
}						t_rp;

t_rp					*rp(t_rp *change_rp);
t_rp					*init_rp(void);
void					free_rp(void);
void					back_to_start_history_rp(void);
void					home_end(long c);
int						str_naa(char *user_in);
void					expand_user_in(void);
t_rp					*rp(t_rp *change_rp);
void					inverse_search_index(int cur_pos[2], int index, size_t prompt_len);
void					reset_rp_to_start(char *prompt);
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
int						str_n(size_t prompt_len);
void					clear_all_line(size_t prompt_len);
void					cur_pos_after_putstr(int *cur_pos, size_t prompt_len);
int						search_last_cur_pos_in_line(int line);
int						search_index(int *cur_pos, size_t prompt_len);
void					move_cursor_to_new_position(int *actual_cur_pos, int *new_cur_pos);
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
void					strmove_cursor(long c);
int						is_print(long c);
void					completion(void);
void					add_new_completion(t_completion **com_lst, char *str);
void					complete_word(t_completion *matches, \
						char *remaider_word, char *path);
void					free_history_list(t_history *history);
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
t_completion			*ret_possible_matches(char *path, int first_word);
char					*cut_word(char cut_symbol, int i);
t_completion			*ret_matches(t_completion *com_lst, char *str_search);
void					free_completion(t_completion *com_lst, \
						t_completion *matches, char *remaider_word, char *path);
int						executable_file(char *file_name, char *path);
t_completion			*add_files_path_env(void);
char					*return_path(char *remaider_word);

/*
** Funcions that make termcaps interactions more readable
*/

void					tc_cursor_up(void);
void					tc_cursor_down(void);
void					tc_cursor_left(void);
void					tc_cursor_right(void);
void					tc_clear_till_end_line(void);
void					tc_cursor_n_right(int n);
void					tc_clear_till_end(void);

#endif
