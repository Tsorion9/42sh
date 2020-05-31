#include "lex.h"

t_token       write_singe_quotes_to_buf(char **user_in, int *index, char *buf,\
    int *buf_index)
{
    write_char_to_buf(*user_in, index, buf, buf_index);
    while ((*user_in)[*index] != '\'')
        write_char_to_buf(*user_in, index, buf, buf_index);
    write_char_to_buf(*user_in, index, buf, buf_index);
    return (get_token_word(user_in, index, buf, buf_index));
}

t_token       write_double_quotes_to_buf(char **user_in, int *index, char *buf,\
    int *buf_index)
{
    write_char_to_buf(*user_in, index, buf, buf_index);
    while (1)
    {
        if ((*user_in)[*index] == '\"' && check_backslash(*user_in, *index - 1))
            break ;
        write_char_to_buf(*user_in, index, buf, buf_index);
    }
    write_char_to_buf(*user_in, index, buf, buf_index);
    return (get_token_word(user_in, index, buf, buf_index));
}
