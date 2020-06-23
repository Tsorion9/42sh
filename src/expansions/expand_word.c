#include "expand.h"
#include "remove_quotes.h"
#include "21sh.h"

/*
** Decide whether to replace dollar or tilda.
** Create new string with replacement
** Free original, update *s
** Increment *pos so that it points to the next char after replacement
*/

static void	replace(char **s, int *position)
{
	if ((*s)[*position] == '$')
		expand_dollar(s, position);
	else if ((*s)[*position] == '~')
		expand_tilda(s, position);
}

static void	step_single_quote(char *s, int *position, t_exp_state *state)
{
	if (s[*position] == '\'')
		*state = norm;
	else if (s[*position] == '\\')
		(*position)++;
	(*position)++;
}

static void	step_double_quote(char **s, int *position, t_exp_state *state)
{
	if ((*s)[*position] == '\"')
		*state = norm;
	else if ((*s)[*position] == '\\')
		(*position)++;
	else if ((*s)[*position] == '$')
	{
		replace(s, position);
		return ;
	}
	(*position)++;
}

static void	step_norm(char **s, int *position, t_exp_state *state)
{
	if ((*s)[*position] == '\\')
	{
		*position += 2;
		return ;
	}
	if ((*s)[*position] == '\'')
	{
		*state = in_sqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '\"')
	{
		*state = in_dqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '~' || (*s)[*position] == '$')
	{
		replace(s, position);
		return ;
	}
	(*position)++;
}

static void	step_norm_assignemt_sup(char **s, int *position, t_exp_state *state)
{
	if ((*s)[*position] == '\'')
	{
		*state = in_sqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '\"')
	{
		*state = in_dqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '~' || (*s)[*position] == '$')
	{
		replace(s, position);
		return ;
	}
	(*position)++;
}

static void	step_norm_assignemt(char **s, int *position, t_exp_state *state, \
			int *equal_sign_detected)
{
	if ((*s)[*position] == '=' && !*equal_sign_detected)
	{
		*equal_sign_detected = 1;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '~' && *equal_sign_detected && *position > 0 && \
		((*s)[*position - 1] == '=' || (*s)[*position - 1] == ':'))
	{
		replace(s, position);
		return ;
	}
	if ((*s)[*position] == '\\')
	{
		*position += 2;
		return ;
	}
	step_norm_assignemt_sup(s, position, state);
}

/*
** 1) Skip everything inside ''; or \$ or \~
** 2) Expand all the symbols one by one (do not apply expansions to the result
** of expansions)
** Implemented as FSM.
**
** STRING MUST BE VALID!!!! no unpaired quotes ; no quoted '0'
*/

char		*expand_word(char *s)
{
	t_exp_state	state;
	int			position;

	state = norm;
	position = 0;
	while (s[position])
	{
		if (state == norm)
			step_norm(&s, &position, &state);
		else if (state == in_sqt)
			step_single_quote(s, &position, &state);
		else
			step_double_quote(&s, &position, &state);
	}
	remove_quotes(s);
	return (s);
}

char		*expand_assignment(char *s)
{
	t_exp_state		state;
	int				position;
	int				equal_sign_detected;

	equal_sign_detected = -1;
	state = norm;
	position = 0;
	while (s[position])
	{
		if (state == norm)
			step_norm_assignemt(&s, &position, &state, &equal_sign_detected);
		else if (state == in_sqt)
			step_single_quote(s, &position, &state);
		else
			step_double_quote(&s, &position, &state);
	}
	return (s);
}

void	expand_inside_wl(void **p)
{
	*p = expand_word(*p);
}

void	expand_inside_arl(void *p)
{
	t_ar	*ar;
	char	*s;

	ar = (t_ar *)p;
	if (ar->what == assignment)
	{
		s = expand_assignment(ar->data);
		ar->data = s;
	}
	else
		expand_inside_wl(&(((t_io_redir *)(ar->data))->where->content));
}

void	expand_simple_cmd(void *c)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)c;
	if (!cmd)
		return ;
	if (cmd->wl)
		deque_apply_inplace(cmd->wl, expand_inside_wl);
	if (cmd->arl)
		deque_apply(cmd->arl, expand_inside_arl);
}

void	expand_pipeline(void *pipeline)
{
	deque_apply(((t_pipeline *)pipeline)->commands, expand_simple_cmd);
}

void	expand_complete_cmd(t_deque *cmd)
{
	deque_apply(cmd, expand_pipeline);
}
