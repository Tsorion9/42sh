#include "lex.h"

t_token	*special_signal_token(void)
{
	t_token	res;

	res.token_type = signal_token;
	res.attribute = NULL;
	return (copy_init_token(res));
}

t_token	stack_special_signal_token(void)
{
	t_token	res;

	res.token_type = signal_token;
	res.attribute = NULL;
	return (res);
}
