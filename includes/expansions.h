#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"

# define VALID_VAR_CHAR			1
# define INVALID_VAR_CHAR		0
# define EXPANSION_FAIL			-1
# define EXPANSION_SUCCESS		100
# define GET_STATUS				1337
# define EXPANSION_EMPTY_WORD	(1 << 0)
# define IN_DQUOTE_STATE		(1 << 0)
# define IN_QUOTE_STATE			(1 << 1)
# define E_ALLOC_MEMORY			"failed to allocate enough memory\n"
# define E_HOME_NOT_SET			"environment value HOME not set\n"
# define E_NO_SUCH_USRDIR		"42sh: no such user or named directory: "
# define E_BAD_SUBSTITUTION		"42sh: bad substitution: "
# define E_PARAM_NULL_OR_UNSET	"parameter null or unset"

int		tilde_expansion(char **s, size_t *i);
int		word_expansion(char **source_word);
void	quote_removal(char **str);

// misk
int		replace_value(char **str, char *value, size_t *start, size_t len);

// errors
int		shell_err(char *error, char *arg);

#endif
