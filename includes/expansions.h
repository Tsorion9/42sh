/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:27:47 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:27:48 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "libft.h"
# include "command_structs.h"

# define VALID_VAR_CHAR			1
# define INVALID_VAR_CHAR		0
# define NOT_IFS				0
# define IFS_CHAR				253
# define EXPANSION_FAIL			-1
# define EXPANSION_SUCCESS		100
# define NEED_FIELD_SPLIT		200
# define GET_STATUS				1337
# define EXPANSION_EMPTY_WORD	(1 << 0)
# define IN_DQUOTE_STATE		(1 << 0)
# define IN_QUOTE_STATE			(1 << 1)
# define E_BAD_SUBSTITUTION		"42sh: bad substitution: "
# define E_CMD_BAD_SUBSTITUTION		"42sh: bad command substitution"
# define E_PARAM_NULL_OR_UNSET	"parameter null or unset"

int			tilde_expansion(char **s, size_t *i, int inside_assignment_word);
int			word_expansion(char **source_word);
char		**field_splitting(const char *source);
t_word_list	*field_splitting_list(const char *source);
void		command_substitution(char **s, int word_state);
int			expasnion_status(int status);
char		**path_clever_split(char *path);

/*
** Quote removal
*/

void		quote_removal(char **str);
char		*pattern_quote_removal(char **pattern);

/*
** Fill IFS characters
*/

void		fill_delimiters_ifs(char **d_ifs, const char *ifs);
void		fill_space_ifs(char **s_ifs, const char *ifs);

/*
** Expansion
*/

void		try_tilde_expansion(char **src_word, size_t *i, int word_state,
							int inside_assignment_word);
void		dollar_expansion(char **src_word, size_t *i, int word_state);
void		pid_expansion(char **src_word, size_t *i);
void		last_cmd_status_expansion(char **src_word, size_t *i, size_t len);
void		length_expansion(char **src_word, int word_state);
void		parameter_expansion(char **src_word, int word_state);
void		var_expansion(char **src_word, size_t *i, int skeep_char,
					int word_state);
void		brace_var_expansion(char **src_word, size_t *i, int skeep_char,
					int word_state);
char		**pathname_expansion(char *word);
t_word_list	*pathname_expansion_list(char *word);

/*
** Parameter expansion special formats
*/

void		use_default_values(char **src_word, char **word,
							char *param_value, int have_colon);
void		indicate_error_if_null_or_unset(char **src_word, char **word,
							char *param, int have_colon);
void		use_alternative_value(char **src_word, char **word,
							char *param_value, int have_colon);
void		assign_default_values(char **src_word, char **word,
							char *param, int have_colon);
void		remove_prefix(char **src_word, char **word, char *param_value,
							int longest);
void		prepare_remove_prefix(char **src_word, char **word,
							char *param_value, char **sep);
void		remove_suffix(char **src_word, char **word, char *param_value,
							int longest);
void		prepare_remove_suffix(char **src_word, char **word,
							char *param_value, char **sep);

/*
** Misc
*/

int			replace_value(char **str, char *value, size_t *start, size_t len);
void		skip_ifs_chars(const char *s, size_t *i,
							const char *s_ifs, const char *d_ifs);
int			is_ifs_char(char c, const char *ifs);
size_t		find_closing_quote(char *data);
int			is_valid_var_char(char c);
int			is_valid_var_name(char *s);
int			is_contain_any_spec(char *s);
void		match_files(t_list **matches, char **path_components,
							char *current_path);
void		del_list(void *mem, size_t garbage);
int			is_greater(void *a, void *b);
char		**clever_list_to_array(t_list *l, int *len);

#endif
