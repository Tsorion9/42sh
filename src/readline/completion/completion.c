/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/10/08 21:26:46 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

// termcap_api.c - работа с курсором
// clear_all_line.c - чистка команды
// user_in - массив положения курсора [положение столбца начинается от 0][положение строки начинается от 0]
// str_n(void) - возвращает количество строк занимаемых командой

static int	is_first_word(int i)
{
	if (rp(NULL)->user_in[i] == '\0')
		i--;
	while (is_print(rp(NULL)->user_in[i]) && i && rp(NULL)->user_in[i] != ' ')
		i--;
	if (!i)
		return (1);
	while ((rp(NULL)->user_in[i] == ' ' || rp(NULL)->user_in[i] == '\t' || \
		rp(NULL)->user_in[i] == '\n') && i)
		i--;
	if (!i)
		return (1);
	return (0);
}

void		completion(void)
{
	char			*remaider_word;
	t_completion	*com_lst;
	t_completion	*matches;
	char			*path;
	int				i;

	// return ; //lol
	i = search_index();
	// ft_printf("\n%d\n%d", i, str_n());
	// while (1);
	path = NULL;
	remaider_word = cut_word(' ', i);
	if (is_first_word(i) && !ft_strchr(remaider_word, '/'))
		com_lst = add_files_path_env();
	else if (!ft_strchr(remaider_word, '/'))
		com_lst = ret_possible_matches(NULL, 0);
	else
	{
		path = return_path(remaider_word);
		com_lst = ret_possible_matches(path, is_first_word(i));
		free(remaider_word);
		remaider_word = cut_word('/', i);
	}
	matches = ret_matches(com_lst, remaider_word);
	if (matches)
		complete_word(matches, remaider_word, path);
	free_completion(com_lst, matches, remaider_word, path);
}
