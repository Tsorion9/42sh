#include "21sh.h"

bool        is_letter(char c)
{
    bool    f;

    f = true;
    if (c == '>' || c == '<' || c == '|' ||\
    c == ' ' || c == '\t' || c == ';' ||\
    c == '\'' || c == 0 || c == '&' ||\
    c == '\"' || is_ws(c))
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

void        write_char_to_buf(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    buf[*buf_index] = user_in[*index];
    (*index)++;
    (*buf_index)++;
}

TOKEN       get_single_quotes(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    write_char_to_buf(user_in, index, buf, buf_index);
    while (user_in[*index] != '\'')
        write_char_to_buf(user_in, index, buf, buf_index);
    write_char_to_buf(user_in, index, buf, buf_index);
    return (get_token_word(user_in, index, buf, buf_index));
}

TOKEN       get_double_quotes(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    write_char_to_buf(user_in, index, buf, buf_index);
    while (1)
    {
        if (user_in[*index] == '\"' && check_backslash(user_in, *index - 1))
            break ;
        write_char_to_buf(user_in, index, buf, buf_index);
    }
    write_char_to_buf(user_in, index, buf, buf_index);
    return (get_token_word(user_in, index, buf, buf_index));
}

char        *create_attribute(char *buf, int buf_index)
{
    char    *attribute;

    buf[buf_index] = 0;
    if (!(attribute = ft_strdup(buf)))
        exit(0);
    return (attribute);
}

TOKEN       get_token_word(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    TOKEN   ret_token;

    while (is_letter(user_in[*index]))
        write_char_to_buf(user_in, index, buf, buf_index);
    if (user_in[*index] == '&' && user_in[*index + 1] != '>')
    {
        write_char_to_buf(user_in, index, buf, buf_index);
        ret_token = get_token_word(user_in, index, buf, buf_index);
    }
    else if (user_in[*index] == '\'' && check_backslash(user_in, *index - 1))
        return (get_single_quotes(user_in, index, buf, buf_index));
    else if (user_in[*index] == '\"' && check_backslash(user_in, *index - 1))
        return (get_double_quotes(user_in, index, buf, buf_index));
    else if (!(check_backslash(user_in, *index - 1)))
    {
        write_char_to_buf(user_in, index, buf, buf_index);
        return (get_token_word(user_in, index, buf, buf_index));
    }
    ret_token.token_type = WORD;
    ret_token.attrinute = create_attribute(buf, *buf_index);
    return (ret_token);
}

TOKEN       get_toket_line_separator(int *index)
{
    TOKEN   ret_token;

    ret_token.token_type = LINE_SEPARATOR;
    (*index)++;
    return (ret_token);
}

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

TOKEN       get_and_greator(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    TOKEN   ret_token;

    if (user_in[*index + 1] == '>')
    {
        ret_token.token_type = AND_GREATOR;
        (*index) += 2;
    }
    else
    {
        write_char_to_buf(user_in, index, buf, buf_index);
        ret_token = get_token_word(user_in, index, buf, buf_index);
    }
    return (ret_token);
}

TOKEN       get_token_number(char *user_in, int *index, char *buf,\
    int *buf_index, int prev_token)
{
    TOKEN   ret_token;

    while (is_digit(user_in[*index]))
        write_char_to_buf(user_in, index, buf, buf_index);
    if (user_in[*index] == '>' || user_in[*index] == '<')
    {
        ret_token.token_type = NUMBER;
        ret_token.attrinute = create_attribute(buf, *buf_index);
    }
    else if (is_letter(user_in[*index]) || user_in[*index] == '\'' ||\
    user_in[*index] == '\"')
        ret_token = get_token_word(user_in, index, buf, buf_index);
    else if (prev_token == LESS_AND || prev_token == GREATER_AND ||\
    prev_token == -1)
    {
        ret_token.token_type = NUMBER;
        ret_token.attrinute = create_attribute(buf, *buf_index);
    }
    else
        ret_token = get_token_word(user_in, index, buf, buf_index);
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
    if (is_ws(user_in[index]))
        skip_ws(user_in, &index);
    if (!user_in[index])
        new_token = get_token_end_line(&index);
    else if (is_digit(user_in[index]))
        new_token = get_token_number(user_in, &index, buf, &buf_index, prev_token);
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
    else if (user_in[index] == '&')
        new_token = get_and_greator(user_in, &index, buf, &buf_index);
    else if (user_in[index] == '\"')
        new_token = get_double_quotes(user_in, &index, buf, &buf_index);
    prev_token = new_token.token_type;
    return (new_token);
}
