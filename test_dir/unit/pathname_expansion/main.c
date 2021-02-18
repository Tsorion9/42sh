#include <stdio.h>
#include "libft.h"

char **pathname_expansion(const char *word);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./expand WORD\n");
		return (1);
	}
	pathname_expansion(argv[1]);
	return (0);
}
