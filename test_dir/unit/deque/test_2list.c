#include <stdio.h>
#include <unistd.h>
#include "t2list.h"

#define USAGE "Usage: \na NUM - add number\nd - del first\np - print all \n"

void	del(void *data)
{
	free(data);
}

void	print_num(void *data)
{
	printf("%d\n", *(int *)data);
}

int	main()
{
	char	buf[12];
	int		nchar;
	t_2list	*l;
	int		*n;

	l = NULL;
	printf("%s\n", USAGE);
	while ((nchar = read(0, &buf, 11)) > 0)
	{
		buf[nchar] = 0;
		if (*buf == 'd')
			lst2del_one(&l, del);
		else if (*buf == 'a')
		{
			n = xmalloc(sizeof(int));
			*n = ft_atoi(buf + 1);
			lst2_add(&l, n);
		}
		else if (*buf == 'd')
			lst2del_one(&l, del);
		else if (*buf == 'p')
			lst2_apply(l, print_num);
		else
		{
			printf("Unknown command: %s\n", buf);
			printf("%s\n", USAGE);
		}
	}
	printf("End of input!\n");
	lst2_apply(l, print_num);
	lst2del(&l, del);
	return(0);
}
