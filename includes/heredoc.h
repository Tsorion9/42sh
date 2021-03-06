#ifndef HEREDOC_H
# define HEREDOC_H

# define ADD_DELIMITER		1
# define ADD_VALUE			2
# define CLEAN_HEREDOC		3
# define NEED_EXPAND_HERE	4
# define HEREDOC_WARNING	"42sh: warning: here-document delimeted by EOF"

typedef struct	s_heredoc
{
	char				**value;
	char				*delimiter;
	struct s_heredoc	*next;
}				t_heredoc;

void			heredoc_action(int action, char *del, char **address_value,
							int *heredoc_sigint);
int				contain_quote(const char *s);
char			*read_heredoc_value(char *delimiter, int *heredoc_sigin);

/*
** Clean routines
*/

void			clean_all_heredoc(t_heredoc **heredoc);
void			delete_heredoc(t_heredoc **heredoc);


#endif
