#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int		main(void)
{
	int	fd = open("test", O_RDWR);
	int	i = 0;
	char buf[1];

	if (fork() == 0)
	{
		while (i < 5)
		{
			read(fd, buf, 1);
			write(1, buf, 1);
			i++;
		}
		close(fd);
	}
	else
	{
		wait(NULL);
		while (i < 5)
		{
			read(fd, buf, 1);
			write(1, buf, 1);
			i++;
		}
	}
	return (0);
}
