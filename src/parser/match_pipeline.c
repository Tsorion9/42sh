#include "parser.h"

static void	enter(t_deque **tokbuf_l, t_pipeline **pipeline)
{
	*tokbuf_l = NULL;
	*pipeline = malloc(sizeof(t_pipeline));
	if (*pipeline)
	{
		(*pipeline)->bang = 0;
		(*pipeline)->commands = NULL;
	}
}

static int	exit_(\
					t_deque **command,
					t_pipeline *pipeline,\
					t_deque **tokbuf_l,\
					t_deque	**tokbuf_g,\
					int status
					)
{
	if (status == PARSER_FAILURE)
	{
		if (pipeline->bang)
			ungett(tokbuf_g, tokbuf_l);
		free(pipeline);
		return (PARSER_FAILURE);
	}
	push_back(command, pipeline);
	return (PARSER_SUCCESS);
}

int			match_pipeline(t_deque **command, t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_pipeline	*pipeline;
	int			exit_status;

	enter(&tokbuf_l, &pipeline);
	if (gett(tokbuf_g, &tokbuf_l)->token_type != bang)
		ungett(tokbuf_g, &tokbuf_l);
	else 
		pipeline->bang = 1;
	exit_status = match_pipe_sequence(pipeline, tokbuf_g);
	return (exit_(command, pipeline, &tokbuf_l, tokbuf_g, exit_status));
}
