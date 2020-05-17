#include "lex.h"

t_token       get_token_pipe(int *index)
{
    t_token   ret_token;

    ret_token.token_type = PIPE;
    (*index)++;
    return (ret_token);
}
