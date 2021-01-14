#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"

# define E_ALLOC_MEMORY		"failed to allocate enough memory\n"
# define E_HOME_NOT_SET		"environment value HOME not set\n"
# define E_NO_SUCH_USRDIR	"21sh: no such user or named directory: "

int		tilde_expansion(char **s, size_t *i);

#endif
