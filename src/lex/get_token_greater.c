#include "lex.h"

t_token       get_token_greater(char *user_in, int *index)
{
    t_token   ret_token;

    ret_token.token_type = GREATER;
    (*index)++;
    if (user_in[*index] == '>')
    {
        ret_token.token_type = GREATER_GREATER;
        (*index)++;
    }
    else if (user_in[*index] == '&')
    {
        ret_token.token_type = GREATER_AND;
        (*index)++;
    }
    return (ret_token);
}
