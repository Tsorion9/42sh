#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int main(int argc, char **argv)
{
	if (argc != 4) {
		printf("Usage ./match string 'pattern' not_quoted\n");
		exit(1);
	}
	printf("%d\n", ft_clever_match(argv[1], argv[2], argv[3]));
	return (0);
}
