#include <stdio.h>
#include "expansions.h"

char  *pattern_quote_removal(char **pattern);

int main(int argc, char **argv)
{
	char **splitted;
	char *arg;

	if (argc != 2) {
		printf("Usage ./path_split <some/path>\n");
		exit(1);
	}
	arg = strdup(argv[1]);
	splitted = path_clever_split(arg);
	for (int i = 0; splitted[i]; ++i)
		printf(splitted[i + 1] ? "%s " : "%s\n", splitted[i]);
	for (int i = 0; splitted[i]; ++i)
		free(splitted[i]);
	free(splitted);
	free(arg);
	return (0);
}
