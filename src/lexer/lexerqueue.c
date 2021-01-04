#include "NewLexer.h"

t_queue	*create_new_queue(char brace)
{
	t_queue	*fresh;

	fresh = (t_queue*)malloc(sizeof(t_queue));
	if (!fresh)
		return (NULL);
	fresh->brace = brace;
	fresh->next = NULL;
	return (fresh);
}

void	push(t_lexer_state *token, char brace)
{
	t_queue *new_head;

	if (token->head == NULL)
		token->head = create_new_queue(brace);
	else
	{
		new_head = create_new_queue(brace);
		new_head->next = token->head;
		token->head = new_head;
	}
}

void	pop(t_lexer_state *token, char brace)
{
	t_queue	*to_delete;

	if (token->head == NULL)
		return ;
	if (brace == token->head->brace)
	{
		to_delete = token->head;
		token->head = token->head->next;
		free(to_delete);
	}
}