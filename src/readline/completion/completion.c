/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2021/01/04 18:06:33 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "inc21sh.h"
// delete
#include "hashtable.h"

int					complection_get_remainder_word(char **remainder_word)
{
	int		com_case;
	int		i;

	i = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	if ((com_case = find_complection_pos(rp(NULL)->user_in, i))
			== COM_VAR_WORD_BRACE)
		return (0);
	if ((*(remainder_word) = tab_cut_word(rp(NULL)->user_in, i))
		&& com_case == COM_VAR)
		*(remainder_word) = cut_uncut_remainder_word(*(remainder_word));
	else if (*(remainder_word) && com_case == COM_VAR_WORD_DOLLAR)
		*(remainder_word) = cut_uncut_remainder_word_dol(*(remainder_word));
	return (com_case);
}

t_completion		*complection_get_matches(int com_case,
					char **remainder_word, t_completion **com_lst, char **path)
{
	int		i;

	i = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	if (com_case == COM_CMD && !ft_strchr(*(remainder_word), '/'))
		*(com_lst) = add_files_path_env();
	else if (com_case == COM_FILE && !ft_strchr(*(remainder_word), '/'))
		*(com_lst) = ret_possible_matches(NULL, 0);
	else if (com_case == COM_VAR || com_case == COM_VAR_WORD_DOLLAR)
		*(com_lst) = ret_possible_vars();
	else
	{
		*(path) = return_path(*(remainder_word));
		*(com_lst) = ret_possible_matches(*(path), com_case);
		free(*(remainder_word));
		*(remainder_word) = tab_cut_word(rp(NULL)->user_in, i);
	}
	return (ret_matches(*(com_lst), remainder_word));
}

void				completion(void)
{
	char			*remainder_word;
	t_completion	*com_lst;
	t_completion	*matches;
	char			*path;
	int				com_case;

	t_hashdata *hd = hash_api_init_hash_data();

	hash_api_insert_hash_value("cat", "!!!", hd);
	hash_api_insert_hash_value("abc", "123", hd);
	hash_api_insert_hash_value("cba", "321", hd);
	hash_api_insert_hash_value("cat", "'      '", hd);
	
	hash_api_print_hash_table(hd);

	// char *x = ft_strdup("AA");
	// while (x[0] < 120)
	// {
	// 	x[1] = 65;
	// 	while (x[1] < 120)
	// 	{
	// 		hash_api_insert_hash_value(x, "!!!", hd);
	// 		x[1]++;
	// 	}
	// 	x[0]++;
	// }
	
	// ft_printf("%c%c%c %c%c", 70, 70, 70, 120, 90);
	// ft_printf("%d %d", hash_api_hash_function("fJ"), hash_api_hash_function("gk"));
	return ;
	path = NULL;
	com_lst = NULL;
	com_api_clear_till_end();
	if (!(com_case = complection_get_remainder_word(&remainder_word)))
		return ;
	if ((matches = complection_get_matches(com_case,
			&remainder_word, &com_lst, &path)))
		matches->com_type = com_case;
	if (com_case == COM_CMD || com_case == COM_FILE)
		com_api_print_suggestion(matches, remainder_word, path);
	else if (com_case == COM_VAR || com_case == COM_VAR_WORD_DOLLAR)
		com_api_print_var_suggestion(matches, remainder_word, path);
	free_completion(com_lst, matches, remainder_word, path);
}
