#include "parser.h"
#include "libft.h"

void	print_op(t_token_type t)
{
	if (t == sep)
		ft_fprintf(2, "%s\n", ";");
	if (t == greater)
		ft_fprintf(2, "%s\n", ">");
	if (t == less)
		ft_fprintf(2, "%s\n", ">");
	if (t == gr_and)
		ft_fprintf(2, "%s\n", ">&");
	if (t == lessand)
		ft_fprintf(2, "%s\n", "<&");
	if (t == dless)
		ft_fprintf(2, "%s\n", "<<");
	if (t == dgreat)
		ft_fprintf(2, "%s\n", ">>");
	if (t == pipel)
		ft_fprintf(2, "%s\n", "|");
	if (t == bang)
		ft_fprintf(2, "%s\n", "!");
	else
		return ;

}

void	print_token(t_token *token)
{
	(void)token;
	if (token->attribute)
		ft_fprintf(2, "%s\n", token->attribute);
	else
		print_op(token->token_type);
}

void	syntax_error(t_token *token)
{
	ft_fprintf(2, "%s", "Syntax error at token: ");
	print_token(token);
}
