#include "21sh.h"

static void	wordmove_right(void)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(rp()->user_in);
    while ((i = search_index()) < len)
    {
        if (ft_isspace(rp()->user_in[i]))
		    move_cursor(RIGHT_ARROW);
        else
            break ;
    }
    while ((i = search_index()) < len)
    {
        if (!ft_isspace(rp()->user_in[i]))
		    move_cursor(RIGHT_ARROW);
        else
            break ;
    }
}

static void	wordmove_left(void)
{
	int i;

    while ((i = search_index() - 1) >= 0)
    {
        if (ft_isspace(rp()->user_in[i]))
		    move_cursor(LEFT_ARROW);
        else
            break ;
    }
    while ((i = search_index() - 1) >= 0)
    {
        if (!ft_isspace(rp()->user_in[i]))
		    move_cursor(LEFT_ARROW);
        else
            break ;
    }
}

void		wordmove_cursor(long c)
{
	if (c == CTRL_LEFT)
		wordmove_left();
	else
		wordmove_right();
}
