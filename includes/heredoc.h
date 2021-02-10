#ifndef HEREDOC_H
# define HEREDOC_H

# define ADD_DELIMITER		1
# define ADD_VALUE			2
# define CLEAN_HEREDOC		3
# define HEREDOC_WARNING	"42sh: warning: here-document delimeted by EOF"

typedef struct	s_heredoc
{
	char				**value;
	char				*delimiter;
	struct s_heredoc	*next;
}				t_heredoc;

void			heredoc_action(int action, char *del, char **address_value, int *heredoc_sigint);
void			clean_all_heardoc(t_heredoc **heredoc);

#endif
