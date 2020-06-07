#include "21sh.h"

/*
** Удаляет все лишние символы backslash
*/

/*static void delete_backslash(char *str)
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
            tmp = ft_strdup(str + i + (bs - (bs / 2)));
            ft_strcpy(str + i, tmp);
            free(tmp);
            while (str[i] == '\\')
                i++;
        }
        i++;
    }
}*/

/*
** Расширение тильды
*/

static void tilde_expansion(char *str, int start)
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

/*
** Расширение параметров
*/

static void parameter_expansion(char *str, int start)
{
    char    *parameter;
    char    remainder[BUFFSIZE];
    char    par_name[BUFFSIZE];
    int     i;

    i = start + 1;
    while (str[i] != 0 && str[i] != ' ' && str[i] != '/'\
        && str[i] != '\t' && str[i] != '\n')
        i++;
    ft_strcpy(par_name, str);
    par_name[i] = 0;
    if ((parameter = getenv(par_name + start + 1)) == NULL)
    {
        if ((parameter = (char*)malloc(sizeof(char))) == NULL)
            exit(0);
        parameter[0] = 0;
    }
    ft_strcpy(remainder, str + i);
    ft_strcpy(str + start, parameter);
    ft_strcpy(str + start + ft_strlen(parameter), remainder);
    if (parameter[0] == 0)
        free(parameter);
}

static void expansion_sup(char *str, int i, char *flag)
{
    if (str[i] == *flag  && *flag == '\'')
        *flag = 0;
    else if (str[i] == '\"' && str[i] == *flag\
       && check_backslash(str, i - 1) == 1)
        *flag = 0;
    else if ((str[i] == '\'' || str[i] == '\"') && *flag == 0\
        && check_backslash(str, i - 1) == 1)
        *flag = str[i];
}

/*
** Дополняет расширениями тильды и параметров
*/

char        *expansion(char *user_in, char **env)
{
    char    str[BUFFSIZE];
    char    flag;
    int     i;

	(void)env;
    if (user_in == NULL)
        exit(0);
    ft_strcpy(str, user_in);
    free(user_in);
    flag = 0;
    i = 0;
    while (str[i] != 0)
    {
        expansion_sup(str, i, &flag);
        if (str[i] == '~' && flag == 0)
            tilde_expansion(str, i);
        else if (str[i] == '$' && flag != '\''\
            && check_backslash(str, i - 1) == 1)
            parameter_expansion(str, i);
        i++;
    }
    //delete_backslash(str);
    return (ft_strdup(str));
}
