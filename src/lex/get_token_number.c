#include "lex.h"

t_token       get_token_number(char **user_in, int *index, char *buf,\
    int *buf_index, int prev_token)
{
    t_token   ret_token;

    while (is_digit((*user_in)[*index]))
        write_char_to_buf(*user_in, index, buf, buf_index);
    if ((*user_in)[*index] == '>' || (*user_in)[*index] == '<')
    {
        ret_token.token_type = NUMBER;
        ret_token.attribute = create_attribute(buf, *buf_index);
    }
    else if (is_letter((*user_in)[*index]) || (*user_in)[*index] == '\'' ||\
    (*user_in)[*index] == '\"')
        ret_token = get_token_word(user_in, index, buf, buf_index);
    else if (prev_token == LESS_AND || prev_token == GREATER_AND)
    {
        ret_token.token_type = NUMBER;
        ret_token.attribute = create_attribute(buf, *buf_index);
    }
    else
        ret_token = get_token_word(user_in, index, buf, buf_index);
    return (ret_token);
}
