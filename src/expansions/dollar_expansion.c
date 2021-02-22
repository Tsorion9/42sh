/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:51:39 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:55:44 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/*
** Ожидается строка с балансом строк
*/

static size_t	find_closing_brace(char *src_word, size_t i)
{
	char	o_brace;
	char	c_brace;
	char	c;
	int		opens;

	o_brace = src_word[i];
	c_brace = o_brace == '{' ? '}' : ')';
	opens = 1;
	while (opens && ++i)
	{
		c = src_word[i];
		if ((c == '"' || c == '\'') && src_word[i - 1] != '\\')
			i += find_closing_quote(src_word + i);
		if (src_word[i - 1] != '\\')
		{
			if (c == o_brace)
				opens++;
			else if (c == c_brace)
				opens--;
		}
	}
	return (i);
}

static void		perform_expansion(char **src, int word_state, size_t *i,
								void (*expand)(char **s, int word_state))
{
	char	*s;
	size_t	j;

	j = find_closing_brace(*src, *i + 1);
	s = ft_strsub(*src, *i + 2, j - *i - 2);
	expand(&s, word_state);
	if (expasnion_status(GET_STATUS) != EXPANSION_FAIL)
		replace_value(src, s, i, j + 1 - *i);
	free(s);
}

/*
** perform variable (parameter) expansion.
**
** syntax           POSIX description   var defined     var undefined
** ======           =================   ===========     =============
** ${var}           Substitute          var             void
** ${var:-word}     Use Deflt Values    var             word
** ${var-word}      Use Deflt Values    var             void
** ${var:?message}  Error if NULL/Unset var             print message and exit
**                                                      shell, (if message is
**														empty,print "var:
**                                                      parameter not set")
** ${#var}          Calculate String Length
*/

static void		perform_parameter_expansion(char **src_word, size_t *i,
										int word_state)
{
	char	*s;
	size_t	j;

	j = find_closing_brace(*src_word, *i + 1);
	s = ft_strsub(*src_word, *i + 2, j - *i - 2);
	if (s && *s == '\0')
	{
		ft_fprintf(STDERR_FILENO, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
	}
	else if (s[0] == '#')
		perform_expansion(src_word, word_state, i, &length_expansion);
	else if (ft_strequ(s, "?"))
		last_cmd_status_expansion(src_word, i, 4);
	else
		perform_expansion(src_word, word_state, i, &parameter_expansion);
	free(s);
}

void			dollar_expansion(char **src_word, size_t *i, int word_state)
{
	if ((*src_word)[*i + 1] == '{')
		perform_parameter_expansion(src_word, i, word_state);
	else if ((*src_word)[*i + 1] == '(')
		perform_expansion(src_word, word_state, i, &command_substitution);
	else if ((*src_word)[*i + 1] == '$')
		pid_expansion(src_word, i);
	else if ((*src_word)[*i + 1] == '?')
		last_cmd_status_expansion(src_word, i, 2);
	else if (is_valid_var_char((*src_word)[*i + 1]))
		var_expansion(src_word, i, 1, word_state);
	else
		(*i)++;
}
