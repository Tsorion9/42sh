#include <stdio.h>
#include "expansions.h"

char  *pattern_quote_removal(char **pattern);

int main(int argc, char **argv)
{
	char *s;
	char *arg;

	if (argc != 2) {
		printf("Usage ./unquote string\n");
		exit(1);
	}
	arg = strdup(argv[1]);
	s = pattern_quote_removal(&arg); 
	printf("%s:%s\n", arg, s);
	free(s);
	free(arg);
	return (0);
}
