#ifndef STR_REPLACE_H
# define STR_REPLACE_H

char	*str_repl(char *s, int start, int end, char *value);
void	str_repl_inplace(char **s, int start, int end, char *value);

#endif
