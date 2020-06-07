#include "lex.h"

t_token       get_token_and_greater(char **user_in, int *index, char *buf,\
    int *buf_index)
{
    t_token   ret_token;

    if ((*user_in)[*index + 1] == '>')
    {
        ret_token.token_type = AND_GREATOR;
        (*index) += 2;
    }
    else
    {
        write_char_to_buf(*user_in, index, buf, buf_index);
        ret_token = get_token_word(user_in, index, buf, buf_index);
    }
    return (ret_token);
}
