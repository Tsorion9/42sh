#include "parser.h"
#include <stdio.h>

void print_words(t_word_list *words)
{
    t_word_list *tmp;

    tmp = words;
    printf("\e[0;34m%21s = ", "words");
    while (tmp)
    {
        printf((tmp->next) ? "%s " : "%s", tmp->word);
        tmp = tmp->next;
    }
    printf("\n");
}

char *get_separator(t_separator type)
{
    if (type == SEP_SEMICOL)
        return (";");
    else if (type == SEP_BG)
        return ("&");
    else if (type == SEP_NEWLINE)
        return ("\\n");
    else
        return ("NONE");
}

void print_simple_cmd(t_simple_cmd *simple_cmd)
{
    //printf("\e[0;34m%21s = %d\n", "flags", simple_cmd->flags);
    print_words(simple_cmd->words);
    print_redirect(simple_cmd->redirects);
}

void print_brace_group(t_brace_group *brace_group)
{
    t_compound_list *compound_lst;

    compound_lst = brace_group->compound_list;
    while (compound_lst != NULL)
    {
        printf("\e[0;34m%21s = %s\n", "separator", get_separator(compound_lst->separator));
        print_and_or(compound_lst->and_or);
        compound_lst = compound_lst->next;
    }
    print_redirect(brace_group->redirects);
}

void print_subshell(t_subshell *subshell)
{
    t_compound_list *compound_lst;

    compound_lst = subshell->compound_list;
    while (compound_lst != NULL)
    {
        printf("\e[0;34m%21s = %s\n", "separator", get_separator(compound_lst->separator));
        print_and_or(compound_lst->and_or);
        compound_lst = compound_lst->next;
    }
    print_redirect(subshell->redirects);
}
