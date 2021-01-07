#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>

typedef struct	s_queue
{
    char				brace;
    struct s_queue		*next;
}				t_queue;

typedef enum	e_tokens
{
    ERROR,
    START,
    WORD,
    IO_NUMBER,
    AND_IF,
    OR_IF,
    DLESS,
    DGREAT,
    LESS,
    GREAT,
    LESSAND,
    GREATAND,
    BG,
    PIPE,
    PIPE_NEWLINE,
    SEMICOL,
    NEWLINE,
    SIGNAL,// Пока не используется
    LBRACE,
    RBRACE,
    LBRACKET,
    RBRACKET,
    TOKEN_END
}				t_tokens;

typedef struct	s_toke
{
    t_tokens			tk_type;
    size_t				tk_len;
    char				*value;
    size_t				str_index;
    int					flags;
    t_queue				*head;
}				t_lexer_state;

typedef struct	s_token
{
    char				*value;
    t_tokens			tk_type;
}				t_token;

#endif
