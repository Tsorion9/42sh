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
