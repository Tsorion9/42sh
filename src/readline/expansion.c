#include "21sh.h"

void        delete_backslash(char *str)
{
    int     i;
    int     z;
    int     bs;
    char    *tmp;

    i = 0;
    while (str[i] != 0)
    {
        if (str[i] == '\\')
        {
            bs = 0;
            z = i;
            while (str[z] == '\\')
            {
                z++;
                bs++;
            }
            bs = bs - (bs / 2);
            tmp = ft_strdup(str + i + bs);
            ft_strcpy(str + i, tmp);
            free(tmp);
            while (str[i] == '\\')
                i++;
        }
        i++;
    }
}

void        tilde_expansion(char *str, int start)
{
    char    *tilde;
    char    remainder[BUFFSIZE];

    if (((tilde = getenv("HOME"))) == NULL)
        return ;
    if (start == 0 && str[start + 1] == '/')
    {
        ft_strcpy(remainder, str + 1);
        ft_strcpy(str, tilde);
        ft_strcpy(str + ft_strlen(tilde), remainder);
    }
    else if ((str[start - 1] == ' ' || str[start - 1] == '\t'\
        || str[start - 1] == '\n') && str[start + 1] == '/')
    {
        ft_strcpy(remainder, str + start + 1);
        ft_strcpy(str + start, tilde);
        ft_strcpy(str + start + ft_strlen(tilde), remainder);
    }
}

void        parameter_expansion(char *str, int start)
{
    char    *parameter;
    char    remainder[BUFFSIZE];
    int     i;

    parameter = getenv(str + start + 1);
    if (parameter == NULL)
        return ;
    i = start;
    while (str[start] != 0 && str[start] != '\n'\
        && str[start] != '\t' && str[start] != ' ')
        start++;
    ft_strcpy(remainder, str + start);
    ft_strcpy(str + i, parameter);
    ft_strcpy(str + i + ft_strlen(parameter), remainder);
}

char        *expansion(char *user_in, char **env)
{
    char    str[BUFFSIZE];
    char    flag;
    int     i;

    if (user_in == NULL)
        exit(0);
    ft_strcpy(str, user_in);
    flag = 0;
    i = 0;
    while (str[i] != 0)
    {
        if (str[i] == flag  && flag == '\'')
            flag = 0;
        else if (str[i] == '\"' && str[i] == flag\
            && check_backslash(user_in, i - 1) == 1)
            flag = 0;
        else if ((str[i] == '\'' || str[i] == '\"') && flag == 0\
            && check_backslash(user_in, i - 1) == 1)
            flag = str[i];
        else if (str[i] == '~' && flag == 0)
            tilde_expansion(str, i);
        else if (str[i] == '$' && flag != '\''\
            && check_backslash(str, i) == 1)
            parameter_expansion(str, i);
        i++;
    }
    delete_backslash(str);
    ft_putstr(str);
}
