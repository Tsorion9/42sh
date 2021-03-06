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
	int	flag;

	i = 0;
	flag = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
	{
		flag = 1;
		i++;
	}
	if (!flag)
		return (0);
	return (i);
}

static int	word_history(char *s)
{
	int i;

	i = 0;
	while (is_valid_var_char(s[i]))
		i++;
	return (i);
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

static int	substitute_history_value(char **cur, int end, char **s)
{
	char	*substr;
	char	*expanded;
	size_t	i;
	size_t	s_len;

	i = ft_strlen(*s) - ft_strlen(*cur);
	substr = ft_strsub(*cur, 0, end + 1);
	expanded = search_history_subtitution(substr);
	if (expanded == NULL)
	{
		ft_fprintf(STDERR_FILENO, "%s %s\n", E_EVENT_NOT_FOUND, substr);
		ft_strdel(&substr);
		return (EXPANSION_FAIL);
	}
	else
		replace_value(s, expanded, &i, end + 1);
	s_len = ft_strlen(*s);
	if (s_len)
		add_to_start_history_lexer(rp(NULL)->history, *s, s_len);
	*cur = next_unquoted_char(*s, '!');
	ft_strdel(&expanded);
	ft_strdel(&substr);
	return (EXPANSION_SUCCESS);
}

void		history_lexer(char **s)
{
	int		end;
	char	*cur;
	int		status;

	status = EXPANSION_SUCCESS;
	if (!s || !*s)
		return ;
	cur = next_unquoted_char(*s, '!');
	while (*cur)
	{
		end = get_end_of_expansion(cur);
		if (end == 0)
			cur++;
		else
		{
			delete_history(rp(NULL)->history);
			status = substitute_history_value(&cur, end, s);
		}
		if (status == EXPANSION_FAIL)
		{
			ft_strdel(s);
			return ;
		}
	}
}
