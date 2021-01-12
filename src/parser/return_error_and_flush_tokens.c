#include "parser.h"

int return_err_and_flush_tokens(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	flush_tokbuf(tokbuf_g, tokbuf_l);
	return (PARSER_ERROR);
}