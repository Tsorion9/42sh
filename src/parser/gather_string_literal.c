/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_string_literal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 12:58:56 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 13:39:59 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "heredoc_utils.h"
#include "memdel3.h"
#include "fuck_norme_lexer_state.h"

static char		*non_interactive_readline(void)
{
	char	*s;
	int		gnl_status;

	gnl_status = get_next_line_wrapper(0, &s);
	if (gnl_status == -1)
		return (NULL);
	if (gnl_status == 0)
	{
		free(s);
		return (NULL);
	}
	s[ft_strlen(s) - 1] = '\0';
	return (s);
}

static char		*temporary_readline_wrapper(char *prompt)
{
	char	*s;

	if (isatty(0))
	{
		s = readline(prompt);
		if (fuck_checklist_signal_state(0, 0))
		{
			if (ft_strcmp(s, "\n"))
				s[ft_strlen(s) > 0 ? ft_strlen(s) - 1 : 0] = 0;
			fuck_norme_lexer_state(1, &s, 0, 0);
			return (NULL);
		}
		if (!s || !*s)
		{
			free(s);
			return (NULL);
		}
		s[ft_strlen(s) - 1] = '\0';
		return (s);
	}
	return (non_interactive_readline());
}

static void		join_literal(void **literal, void **line)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_strjoin((char *)*line, "\n");
	tmp = ft_strjoin((char *)*literal, tmp1);
	memdel3(literal, line, (void **)&tmp1);
	*literal = tmp;
}

char			*gather_string_literal(char *here_eof)
{
	char	*literal;
	char	*line;

	literal = ft_strdup("");
	while (1)
	{
		if (!(line = temporary_readline_wrapper(get_prompt(PS2))))
		{
			if (fuck_checklist_signal_state(0, 0))
			{
				free(literal);
				return (NULL);
			}
			ft_fprintf(2, EOF_WRN_S, here_eof);
		}
		if (!line || ft_strcmp(line, here_eof) == 0)
		{
			free(line);
			if (!*literal)
				ft_memdel((void **)&literal);
			return (literal);
		}
		else
			join_literal((void **)&literal, (void **)&line);
	}
}
