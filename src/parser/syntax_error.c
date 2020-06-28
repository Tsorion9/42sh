/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
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
	if (t == eof)
		ft_fprintf(2, "%s\n", "EOF");
	if (t == __newline)
		ft_fprintf(2, "%s\n", "'\\n'");
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

int		syntax_error_state_action(int request, int param)
{
	static int	error_state;

	if (request == SYNTAX_ERROR_STATE_SET)
	{
		error_state = param;
		return (0);
	}
	return (error_state);
}

void	syntax_error(t_token *token)
{
	if (fuck_checklist_signal_state(0, 0))
		return ;
	ft_fprintf(2, "%s", "Syntax error at token: ");
	print_token(token);
}
