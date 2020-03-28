#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

int     main(void)
{
    char	*arg[] = {"/bin/cat", NULL};
    int	fd = open("test", O_APPEND);

    dup2(fd, STDIN_FILENO);
	int 	pid;
    write(STDOUT_FILENO, "\n", 1);
    if ((pid = fork()) == 0)
    {
        execv("/bin/cat", arg);
    }
    else
    {
        waitpid(pid, NULL, WNOHANG);
    }
    dup2(STDIN_FILENO, STDIN_FILENO);
    return (0);
}
