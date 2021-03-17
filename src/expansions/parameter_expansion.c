/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:45:13 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 18:45:14 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environment.h"

/*
** '-' == использовать значнение word после расширения
** '?' == выводит сообщение об ошибке, если значение unset/null
** '+' == использовать альтернативное значение
** '=' == присвоить значение
** '#' == удалить наименьший префикс
** '##' == удалить наибольший префикс
** '%' == удалить наименьший суффикс
** '%%' == удалить наибольший суффикс
**
** src_word исходное слово
** sep указатель на специальный параметр в src_word
** простыми словами, sep подстрока src_word, указывающая на спец символ
** parameter используется для присваивания значения, если необходимо
*/

static void	var_not_null(char **src_word, char **sep, char *param)
{
	char	c;
	char	*word;
	char	*param_value;
	size_t	i;

	c = **sep;
	word = ft_strdup(*sep + 1);
	param_value = ft_getenv(g_env, param);
	i = 0;
	if (c == '-' || c == '=' || c == '?')
		replace_value(src_word, param_value, &i, ft_strlen(*src_word));
	else if (c == '#')
		prepare_remove_prefix(src_word, &word, param_value, sep);
	else if (c == '%')
		prepare_remove_suffix(src_word, &word, param_value, sep);
	else
	{
		ft_fprintf(2, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
	}
	free(word);
}

/*
** '-' == использовать значнение word после расширения
** '?' == выводит сообщение об ошибке, если значение unset/null
** '+' == использовать альтернативное значение
** '=' == присвоить значение
** '#' == удалить наименьший префикс
** '##' == удалить наибольший префикс
** '%' == удалить наименьший суффикс
** '%%' == удалить наибольший суффикс
**
** src_word исходное слово
** sep указатель на специальный параметр в src_word
** простыми словами, sep подстрока src_word, указывающая на спец символ
** parameter используется для присваивания значения, если необходимо
*/

static void	var_unset_or_empty(char **src_word, char **sep, char *param,
								int have_colon)
{
	char	*word;

	word = ft_strdup(*sep + 1);
	if (**sep == '-')
		use_default_values(src_word, &word, ft_getenv(g_env, param),
				have_colon);
	else if (**sep == '?')
		indicate_error_if_null_or_unset(src_word, &word, param, have_colon);
	else if (**sep == '+')
		use_alternative_value(src_word, &word, ft_getenv(g_env, param),
																have_colon);
	else if (**sep == '=')
		assign_default_values(src_word, &word, param, have_colon);
	else if (**sep == '%' || **sep == '#')
	{
		ft_strdel(src_word);
		*src_word = ft_strnew(0);
		ft_strdel(&word);
	}
	else
	{
		ft_fprintf(2, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
		ft_strdel(&word);
	}
}

static void	perform_parameter_expansion(char **src_word, char *sep)
{
	char	*parameter;
	int		have_colon;
	char	*var_value;

	parameter = ft_strsub(*src_word, 0, (size_t)(sep - *src_word));
	have_colon = 0;
	if (*parameter == '\0' || !is_valid_var_name(parameter))
	{
		ft_fprintf(2, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
		ft_strdel(&parameter);
		return ;
	}
	var_value = ft_getenv(g_env, parameter);
	if (*sep == ':')
	{
		sep++;
		have_colon = 1;
	}
	if (!var_value || !(*var_value))
		var_unset_or_empty(src_word, &sep, parameter, have_colon);
	else
		var_not_null(src_word, &sep, parameter);
	free(parameter);
}

/*
** start string in which perform search
** search string of symbols that need to search
** return a pointer to the found element from search else NULL
*/

static char	*search_separator(char *start, const char *search)
{
	char	*pointer;

	pointer = start;
	while (*pointer)
	{
		if (*pointer == '\'' || *pointer == '"')
			pointer += find_closing_quote(pointer);
		else if (ft_strchr(search, *pointer))
			return (pointer);
		pointer++;
	}
	return (NULL);
}

/*
** '{' src_word '}'
** src_word == parameter( [:][=+-?] | (#[#] | %[%]) )word
** word_state is used to check quote states
*/

void		parameter_expansion(char **src_word, int word_state)
{
	size_t	i;
	char	*sep;

	i = 0;
	sep = search_separator(*src_word, ":-=?+%#");
	if (sep)
		perform_parameter_expansion(src_word, sep);
	else
		brace_var_expansion(src_word, &i, 0, word_state);
	if (expasnion_status(GET_STATUS) == EXPANSION_SUCCESS
		&& !(word_state & IN_QUOTE_STATE) && !(word_state & IN_DQUOTE_STATE))
		expasnion_status(NEED_FIELD_SPLIT);
}
