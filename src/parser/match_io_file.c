#include "parser.h"

static void	figure_out_fd(t_io_redir *redir)
{
	if (redir->fd) /* Nonzero => initialized by user! */
		return ;
	if (redir->operation == greater ||\
		redir->operation == dgreat ||\
		redir->operation == gr_and)
		redir->fd = 1; /* default stdout fd */
}

int	match_io_file(t_io_redir *redir, t_deque **tokbubf_g)
{
	t_deque			*tokbuf_l;
	t_token_type	type;
	t_token			*tok;

	tokbuf_l = NULL;
	type = gett(tokbubf_g, &tokbuf_l)->token_type;
	if (type != less && type != greater && type != gr_and\
			&& type != lessand && type != dgreat && type != clobber)
	{
		ungett(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	redir->operation = type;
	figure_out_fd(redir);
	if ((tok = gett(tokbubf_g, &tokbuf_l))->token_type != word)
	{
		flush_tokbuf(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	ft_lstadd_data(&(redir->where), (void *)(ft_strdup(tok->attribute)), 0);
	erase_tokbuf(&tokbuf_l);
	return (PARSER_SUCCESS);
}
