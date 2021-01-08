#ifndef HEREDOC_H
# define HEREDOC_H

# define ADD_DELIMITER	1
# define ADD_VALUE		2
# define CLEAN_HEREDOC	3

typedef struct	s_heredoc
{
	char				**value;
	char				*delimiter;
	struct s_heredoc	*next;
}				t_heredoc;

void			heredoc_action(int action, char *del, char **address_value);

#endif
