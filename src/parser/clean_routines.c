#include "parser.h"

void clean_command(t_command **command)
{
    if ((*command)->cmd_type == SUBSHELL)
        clean_subshell(&(*command)->subshell);
    else if ((*command)->cmd_type == BRACE_GROUP)
        clean_brace_group(&(*command)->brace_group);
    else
        clean_simple_cmd(&(*command)->simple_cmd);
    free(*command);
    *command = NULL;
}

void clean_pipeline(t_pipeline **pipeline)
{
    t_pipeline *delete;

    while (*pipeline != NULL)
    {
        clean_command(&(*pipeline)->command);
        delete = *pipeline;
        *pipeline = (*pipeline)->next;
        free(delete);
        delete = NULL;
    }
}

void clean_and_or(t_andor_list **and_or)
{
    t_andor_list *delete;

    while (*and_or != NULL)
    {
        clean_pipeline(&(*and_or)->pipeline);
        delete = *and_or;
        *and_or = (*and_or)->next;
        free(delete);
        delete = NULL;
    }
}

void clean_complete_command(t_complete_cmd **complete_cmd)
{
    t_complete_cmd *delete;

    while (*complete_cmd != NULL)
    {
        clean_and_or(&(*complete_cmd)->and_or);
        delete = *complete_cmd;
        *complete_cmd = (*complete_cmd)->next;
        free(delete);
        delete = NULL;
    }
}