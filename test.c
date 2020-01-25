#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

int		main(void)
{
	int		conn[2];
	char	buf[6];
	char	*arg[] = {"/bin/ls", NULL};
	char	*arg1[] = {"/bin/cat", "-e", NULL};
	int		fd = open("test", O_RDWR);

	buf[5] = 0;
	pipe(conn);
	int i = 0;
	if (fork() == 0)
	{
		if (fork() == 0)
		{
			dup2(conn[1], 1);
			close(conn[0]);
			execv("/bin/ls", arg);
		}
		else
		{
			close(conn[1]);
			wait(NULL);
			dup2(conn[0], 0);
			dup2(conn[1], 1);
			execv("/bin/cat", arg1);
		}
	}
	else
	{
		close(conn[1]);
		wait(NULL);
		dup2(conn[0], 0);
		execv("/bin/cat", arg1);
	}
	return (0);
}
