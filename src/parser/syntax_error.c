#include "parser.h"
#include "libft.h"

#define MSG "Printing tokens is not implemented\n"

void	print_token(t_token *token)
{
	(void)token;
	write(1, MSG, ft_strlen(MSG));
}

/*
** WTF, GCC !?
*/
int					ft_fprintf(int fd, const char *format, ...);

void	syntax_error(t_token *token)
{
	ft_fprintf(2, "%s", "Syntax error at token: ");
	print_token(token);
}
