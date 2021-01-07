#include "parser.h"

void clean_compound_list(t_compound_list **compound_list)
{
    t_compound_list *delete;

    while (*compound_list != NULL)
    {
        clean_and_or(&(*compound_list)->and_or);
        delete = *compound_list;
        *compound_list = (*compound_list)->next;
        free(delete);
        delete = NULL;
    }
}