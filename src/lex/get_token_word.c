#include "lex.h"

static int  is_token_assignment_word(char *buf)
{
    char    flag;
    int     i;

    if (!ft_strchr(buf, '=') || buf[0] == '=')
        return (0);
    flag = 0;
    i = 0;
    while (buf[i])
    {
        if (buf[i] == '=' && flag == 0 && check_backslash(buf, i - 1))
            return (1);
        else if (buf[i] == flag  && flag == '\'')
            flag = 0;
        else if (buf[i] == '\"' && buf[i] == flag\
            && check_backslash(buf, i - 1) == 1)
            flag = 0;
        else if ((buf[i] == '\'' || buf[i] == '\"') && flag == 0\
            && check_backslash(buf, i - 1) == 1)
            flag = buf[i];
        i++;
    }
    return (0);
}

t_token     get_token_word(char *user_in, int *index, char *buf,\
    int *buf_index)
{
    t_token   ret_token;

    while (is_letter(user_in[*index]))
        write_char_to_buf(user_in, index, buf, buf_index);
    if (user_in[*index] == '&' && user_in[*index + 1] != '>')
    {
        write_char_to_buf(user_in, index, buf, buf_index);
        ret_token = get_token_word(user_in, index, buf, buf_index);
    }
    else if (user_in[*index] == '\'' && check_backslash(user_in, *index - 1))
        return (write_singe_quotes_to_buf(user_in, index, buf, buf_index));
    else if (user_in[*index] == '\"' && check_backslash(user_in, *index - 1))
        return (write_double_quotes_to_buf(user_in, index, buf, buf_index));
    else if (!(check_backslash(user_in, *index - 1)))
    {
        write_char_to_buf(user_in, index, buf, buf_index);
        return (get_token_word(user_in, index, buf, buf_index));
    }
    ret_token.token_type = WORD;
    if (is_token_assignment_word(buf))
        ret_token.token_type = ASSIGNMENT_WORD;
    ret_token.attribute = create_attribute(buf, *buf_index);
    return (ret_token);
}
