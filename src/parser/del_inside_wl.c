#include "command.h"
#include "parser.h"
#include "deque.h"
#include "libft.h"

void	rm_word(void *word)
{
	free(word);
}

void	del_inside_wl(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}
