#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <termios.h>
#include <term.h>
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

#define BUFFSIZE 4096

/*
** Character key constants
*/

#define LEFT_ARROW 4479771 
#define RIGHT_ARROW 4414235 

#define UP_ARROW  4283163
#define DOWN_ARROW 4348699

#define ALT_LEFT_ARROW 74986827111195
#define ALT_RIGHT_ARROW 73887315483419

#if defined(__APPLE__) || defined(__NetBSD__)

#define ALT_LEFT_ARROW 25115
#define ALT_RIGHT_ARROW 26139

#endif

#ifdef ANTON_UNUSUAL_LAPTOP
#define BACKSPACE 8
#else
#define BACKSPACE 127
#endif

#define DEL 2117294875

#define CTRL_W 23
#define CTRL_Q 17
#define CTRL_R 18
#define CTRL_LEFT 74995417045787
#define CTRL_RIGHT 73895905418011

/*
** Funcions that make termcaps interactions more readable
*/

void		tc_cursor_left(int *cur_pos);
void		tc_cursor_right(int *cur_pos);
void		tc_clear_till_end(void);

int			ft_putint(int c);
char        *readline(void);
void        move_cursor(long c, int *cur_pos, char *user_in);
void        clear_line(int cup_pos);
void        delete_symbol(char *user_in, int *cur_pos);
void        insert_symbol(char *user_in, int *cur_pos, char c);
void        alt_left_right(long c, int *cur_pos, char *user_in);
int         check_backslash(char *user_in, int start_check);
char        *expansion(char *user_in, char **env);
