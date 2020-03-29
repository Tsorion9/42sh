#include "21sh.h"

bool        is_letter(char c)
{
    bool    f;

    f = true;
    if (c == '>' || c == '<' || c == '|' ||\
    c == ' ' || c == '\t' || c == ';' ||\
    c == '\'' || c == 0 || is_ws(c))
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

bool        is_ws(char c)
{
    bool    f;

    f = false;
    if (c == ' ' || c == '\t')
        f = true;
    return (f);
}

TOKEN       get_token_gr(char *user_in, int *index)
{
    TOKEN   ret_token;

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

TOKEN       get_token_le(char *user_in, int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = LESS;
    (*index)++;
    if (user_in[*index] == '<')
    {
        ret_token.token_type = LESS_LESS;
        (*index)++;
    }
    else if (user_in[*index] == '&')
    {
        ret_token.token_type = LESS_AND;
        (*index)++;
    }
    return (ret_token);
}

TOKEN       get_single_quotes(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    buf[*buf_index] = user_in[*index];
    (*index)++;
    (*buf_index)++;
    while (user_in[*index] != '\'')
    {
        buf[*buf_index] = user_in[*index];
        (*index)++;
        (*buf_index)++;
    }
    buf[*buf_index] = user_in[*index];
    (*index)++;
    (*buf_index)++;
    return (get_token_word(user_in, index, buf, buf_index));
}

TOKEN       get_token_word(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    TOKEN   ret_token;

    while (is_letter(user_in[*index]))
    {
        buf[*buf_index] = user_in[*index];
        (*buf_index)++;
        (*index)++;
    }
    if (user_in[*index] == '\'' && user_in[*index - 1] != '\\')
        return (get_single_quotes(user_in, index, buf, buf_index));
    else if (user_in[*index - 1] == '\\')
    {
        buf[*buf_index] = user_in[*index];
        (*buf_index)++;
        (*index)++;
        return (get_token_word(user_in, index, buf, buf_index));
    }
    buf[*buf_index] = '\0';
    ret_token.token_type = WORD;
    if (!(ret_token.attrinute = ft_strdup(buf)))
        exit(0);
    return (ret_token);
}

TOKEN       get_toket_line_separator(int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = LINE_SEPARATOR;
    (*index)++;
    return (ret_token);
}

/*TOKEN       get_double_quotes(char *user_in, int *index, char *buf,\
    int *buf_index)
{

}
*/

TOKEN       get_token_end_line(int *index)
{
    TOKEN   ret_token;

    *index = 0;
    ret_token.token_type = END_LINE;
    return (ret_token);
}

TOKEN       get_token_pipe(int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = PIPE;
    (*index)++;
    return (ret_token);
}

void        skip_ws(char *user_in, int *index)
{
    while (is_ws(user_in[*index]))
        (*index)++;
}

TOKEN       get_next_token(char *user_in)
{
    static int  index = 0;
    static int  prev_token = -1;
    TOKEN       new_token;
    char        buf[BUFFSIZE];
    int         buf_index;

    buf_index = 0;
    if (is_ws(user_in[index]))
        skip_ws(user_in, &index);
    if (!user_in[index])
        new_token = get_token_end_line(&index);
    else if (user_in[index] == '>')
        new_token = get_token_gr(user_in, &index);
    else if (user_in[index] == '<')
        new_token = get_token_le(user_in, &index);
    else if (user_in[index] == '|')
        new_token = get_token_pipe(&index);
    else if (is_letter(user_in[index]))
        new_token = get_token_word(user_in, &index, buf, &buf_index);
    else if (user_in[index] == ';')
        new_token = get_toket_line_separator(&index);
    else if (user_in[index] == '\'')
        new_token = get_single_quotes(user_in, &index, buf, &buf_index);
    return (new_token);
}
