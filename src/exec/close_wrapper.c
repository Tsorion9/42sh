#include <unistd.h>

int	close_wrapper(int fd)
{
	if (fd >= 0)
		return (close(fd));
	return (-1);
}
