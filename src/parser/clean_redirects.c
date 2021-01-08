#include "parser.h"

void	clean_redirector(t_redirector **redirector)
{
	if ((*redirector)->filename)
		ft_strdel(&(*redirector)->filename);
	free(*redirector);
	*redirector = NULL;
}

void	clean_redirects(t_redirect **redirects)
{
	t_redirect *delete;

	while (*redirects != NULL)
	{
		clean_redirector(&(*redirects)->redirector);
		if ((*redirects)->heredoc_value)
			ft_strdel(&(*redirects)->heredoc_value);
		delete = *redirects;
		*redirects = (*redirects)->next;
		free(delete);
		delete = NULL;
	}
}
