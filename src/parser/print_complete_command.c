#include "parser.h"
#include <stdio.h>

char *get_separator_op(t_separator_op separator)
{
    if (separator == OP_NONE)
        return ("NONE");
    else if (separator == OP_SEMICOL)
        return (";");
    else if (separator == OP_BG)
        return ("&");
    else
        return ("UNKNOWN");
}

char *get_type_if(t_type_andor type)
{
    if (type == ANDOR_NONE)
        return ("NONE");
    else if (type == ANDOR_OR)
        return ("||");
    else if (type == ANDOR_AND)
        return ("&&");
    else
        return ("UNKNOWN");
}

void print_and_or(t_andor_list *and_or)
{
    t_andor_list *tmp;

    tmp = and_or;
    while (tmp)
    {
        printf("\e[0;32m%14s = %d\n", "exit status", tmp->exit_status);
        printf("\e[0;32m%10s     = %s\n", "type if", get_type_if(tmp->type_andor));
        print_pipeline(tmp->pipeline);
        tmp = tmp->next;
    }
}

void print_complete_command(t_complete_cmd *complete_cmd)
{
    t_complete_cmd *tmp;

    printf("##########print DEBUG info##########\n");
    tmp = complete_cmd;
    while (tmp)
    {
        printf("\e[0;31mSeparator = %s\n", get_separator_op(tmp->separator_op));
        print_and_or(tmp->and_or);
        tmp = tmp->next;
    }
}