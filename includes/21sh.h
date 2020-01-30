#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <termios.h>
#include <term.h>
#include <fcntl.h>
#include "../libft/includes/libft.h"
#include <stdio.h>

#define BUFFSIZE 4096

struct termios g_settings;

int			ft_putint(int c);
char        *readline(void);
void        move_cursor(long c, int *cur_pos, char *user_in);
void        clear_line(int cup_pos);
void        delete_symbol(char *user_in, int *cur_pos);
void        insert_symbol(char *user_in, int *cur_pos, char c);
void        alt_left_right(long c, int *cur_pos, char *user_in);
