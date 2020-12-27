/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/27 15:12:23 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		completion(void)
{
	char			*remainder_word;
	t_completion	*com_lst;
	t_completion	*matches;
	char			*path;
	int				i;
	int				com_case;

	path = NULL;
	com_api_clear_till_end();
	i = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	if ((com_case = find_complection_pos(rp(NULL)->user_in, i)) == COM_VAR_WORD_BRACE)
		return ;
	if ((remainder_word = tab_cut_word(rp(NULL)->user_in, i))
		&& com_case == COM_VAR)
		remainder_word = cut_uncut_remainder_word(remainder_word);
	if (com_case == COM_CMD && !ft_strchr(remainder_word, '/'))
		com_lst = add_files_path_env();
	else if (com_case == COM_FILE && !ft_strchr(remainder_word, '/'))
		com_lst = ret_possible_matches(NULL, 0);
	else if (com_case == COM_VAR)
		com_lst = ret_possible_vars();
	else
	{
		path = return_path(remainder_word);
		com_lst = ret_possible_matches(path, com_case);
		free(remainder_word);
		remainder_word = tab_cut_word(rp(NULL)->user_in, i);
	}
	matches = ret_matches(com_lst, &remainder_word);
	if (matches)
		matches->com_type = com_case;
	if (com_case == COM_CMD || com_case == COM_FILE)
		com_api_print_suggestion(matches, remainder_word, path);
	else if (com_case == COM_VAR)
		com_api_print_var_suggestion(matches, remainder_word, path);
	free_completion(com_lst, matches, remainder_word, path);
}
