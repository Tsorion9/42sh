#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define USAGE "Usage:\naf N - pushfront\nab N - pushback\ndf - del front\n"\
			"db - del back\nc - clear\np - print\nl length\n"

void	prompt()
{
	printf("%s:", "Enter the command");
	fflush(stdout);
}

void	print_usage()
{
	printf("%s\n", USAGE);
}

void	print_number(void *n)
{
	printf("%d\n", *(int *)n);
}

void	print_deque(t_deque *d)
{
	if (!d)
		printf("Deque is empty!\n");
	else
		lst2_apply(d->first, print_number);
}

void	print_deque_len(t_deque *d)
{
	printf("%d\n", deque_len(d));
}

void	del(void *data)
{
	free(data);
}

int main()
{
	t_deque	*d;
	char	buf[20];
	int		nchar;
	int		*n;

	d = NULL;
	print_usage();
	fflush(stdout);
	prompt();
	while ((nchar = read(0, &buf, 20)))
	{
		buf[nchar] = 0;
		if (buf[0] == 'l')
			print_deque_len(d);
		if (!strncmp(buf, "af", 2))
		{
			n = xmalloc(sizeof(int));
			*n = atoi(buf + 2);
			push_front(&d, n);
		}
		else if (!strncmp(buf, "ab", 2))
		{
			n = xmalloc(sizeof(int));
			*n = atoi(buf + 2);
			push_back(&d, n);
		}
		else if (!strncmp(buf, "db", 2))
		{
			n = pop_back(d);
			if (!n)
				printf("Deque was empty!\n");
			else
				printf("Removed: %d from the end\n", *n);
			free(n);
		}
		else if (!strncmp(buf, "df", 2))
		{
			n = pop_front(d);
			if (!n)
				printf("Deque was empty!\n");
			else
				printf("Removed: %d from the beginning\n", *n);
			free(n);
		}
		else if (*buf == 'p')
			print_deque(d);
		else if (*buf == 'c')
			deque_del(&d, del);
		else 
			print_usage();
		prompt();
	}
	deque_del(&d, del);
	return (0);
}
