/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 17:15:54 by jsance            #+#    #+#             */
/*   Updated: 2021/03/13 17:15:55 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "readline.h"

static int	history_digit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i - 1] == '-')
		return (0);
	return (--i);
}

static int	word_history(char *s)
{
	int i;

	i = 0;
	while (is_valid_var_char(s[i]))
		i++;
	return (--i);
}

/*
** Return NULL if tail not found or can't expand
*/

static int	get_end_of_expansion(char *cur)
{
	int tail;

	tail = 1;
	if (cur[tail] == '!')
		return (tail);
	if (cur[tail] == '-' || ft_isdigit(cur[tail]))
		return (history_digit(cur + tail));
	else if (is_valid_var_char(cur[tail]))
		return (word_history(cur + tail));
	return (0);
}

void		history_lexer(char **s)
{
	int		end;
	char	*cur;
	char	*substr;
	char	*expanded;
	size_t	i;

	i = 0;
	cur = next_unquoted_char(*s, '!');
	while (*cur)
	{
		end = get_end_of_expansion(cur);
		i = ft_strlen(*s) - ft_strlen(cur);
		if (end == 0)
			cur++;
		else
		{
			substr = ft_strsub(cur, 0, end);
			expanded = search_history_subtitution(substr);
			if (expanded == NULL)
			{
				ft_fprintf(STDERR_FILENO, "%s %s", E_EVENT_NOT_FOUND, substr);
				ft_strdel(&substr);
				break ;
			}
			else
				replace_value(s, expanded, &i, end + 1);
			cur = next_unquoted_char(*s, '!');
			ft_strdel(&expanded);
			ft_strdel(&substr);
		}
	}
}
