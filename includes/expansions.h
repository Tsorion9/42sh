#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"

# define EXPANSION_FAIL			0
# define EXPANSION_EMPTY_WORD	(1 << 0)
# define IN_DQUOTE_STATE		(1 << 0)
# define IN_QUOTE_STATE			(1 << 1)
# define E_ALLOC_MEMORY			"failed to allocate enough memory\n"
# define E_HOME_NOT_SET			"environment value HOME not set\n"
# define E_NO_SUCH_USRDIR		"21sh: no such user or named directory: "

int		tilde_expansion(char **s, size_t *i);
int		word_expansion(char **source_word);

#endif
