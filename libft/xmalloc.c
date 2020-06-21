#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void	*xmalloc(size_t n)
{
	void	*res;

	if (!(res = malloc(n)))
		exit(ENOMEM);
	return (res);
}
