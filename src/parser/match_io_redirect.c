#include "parser.h"

t_redirect  *init_redirects()
{
    t_redirect *fresh;

    fresh = (t_redirect*)ft_memalloc(sizeof(t_redirect));
    if (!fresh)
        return (NULL);
    fresh->redirector = (t_redirector*)ft_memalloc(sizeof(t_redirector));
    return (fresh);
}

t_redirect  *create_tail_redirects(t_redirect **head_redirects)
{
    if (*head_redirects == NULL)
    {
        *head_redirects = init_redirects();
        return (*head_redirects);
    }
    else
        return (create_tail_redirects(&(*head_redirects)->next));
}

int 		need_set_default_fd(int action)
{
	static int	is_default_fd_needed;

	if (action == NEED_DEFAULT_FD)
		is_default_fd_needed = 1;
	return (is_default_fd_needed);
}

/*
** [IO_NUMBER]? (io_file | DLESS WORD)
*/

int         match_io_redirect(t_redirect **head_redirects, t_deque **tokbuf_g)
{
    t_deque		*tokbuf_l;
    t_redirect	*tail_redir;

    tokbuf_l = NULL;
    tail_redir = create_tail_redirects(head_redirects);
    if (gett(tokbuf_g, &tokbuf_l)->tk_type != IO_NUMBER)
	{
        ungett(tokbuf_g, &tokbuf_l);
    	need_set_default_fd(NEED_DEFAULT_FD);
	}
    else
        tail_redir->redirector->fd = ft_atoi(deque_n_th(tokbuf_l, 0)->value);
    if (match_io_file(&tail_redir, tokbuf_g) == PARSER_SUCCES
        || match_dless_word(&tail_redir, tokbuf_g) == PARSER_SUCCES)
    {
        erase_tokbuf(&tokbuf_l);
        return (PARSER_SUCCES);
    }
    return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
}