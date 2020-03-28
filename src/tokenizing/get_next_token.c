#include "21sh.h"

bool        is_letter(char c)
{
    bool    f;

    f = true;
    if (c == '>' || c == '<' || c == '|' ||\
    c == ' ' || c == '\t' || c == ';')
        f = false;
    return (f);
}

bool        is_digit(char c)
{
    bool    f;

    f = false;
    if (c >= '0' && c <= '9')
        f = true;
    return (f);
}

TOKEN       get_token_gr(char *user_in, int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = GREATER;
    (*index)++;
    if (user_in[*index] == '>')
        ret_token.token_type = GREATER_GREATER;
    else if (user_in[*index] == '&')
        ret_token.token_type = GREATER_AND;
    return (ret_token);
}

TOKEN       get_token_le(char *user_in, int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = LESS;
    (*index)++;
    if (user_in[*index] == '<')
        ret_token.token_type = LESS_LESS;
    else if (user_in[*index] == '&')
        ret_token.token_type = LESS_AND;
    return (ret_token);
}

TOKEN       get_token_let(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    TOKEN   ret_token;

    while (is_letter(user_in[*index]))
    {
        buf[*buf_index] = user_in[*index];
        (*buf_index)++;
        *(index)++;
    }
    buf[*buf_index] = '\0';
    ret_token.token_type = WORD;
    if (!(ret_token.attrinute = ft_strdup(buf)))
        exit(0);
    return (ret_token);
}

TOKEN       get_next_token(char *user_in)
{
    static int  index = 0;
    static int  prev_token = -1;
    TOKEN       new_token;
    char        buf[BUFFSIZE];
    int         buf_index;

    buf_index = 0;
    if (user_in[index] == '>')
        new_token = get_token_gr(user_in, &index);
    else if (user_in[index] == '<')
        new_token = get_token_le(user_in, &index);
    else if (user_in[index] == '|')
        new_token.token_type = PIPE;
    else if (is_letter(user_in[index]))
        new_token = get_token_let(user_in, &index, buf, &buf_index);
}
