#include "libft.h"
#include "str_replace.h"

int main(int argc, char **argv)
{
	int	start;
	int	end;
	char *src;
	char *dst;
	char *new;

	if (argc < 5)
	{
		ft_printf("%s\n", "Usage: ./test string start end value");
		return (1);
	}
	new = str_repl(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3]), argv[4]);
	ft_printf("Result: %s\n", new);
	free(new);
	return (0);
}
