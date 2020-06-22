#include "remove_quotes.h"

#include <stdio.h>
#include <unistd.h>

int main() 
{
	char	c[50];
	int		nbytes;

	while ((nbytes = read(0, c, 50)) > 0)
	{
		c[nbytes] = 0;
		remove_quotes(c);
		printf("%s\n", c);
	}
	return (0);
}
