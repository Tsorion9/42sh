/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/10/16 20:35:28 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

// termcap_api.c - работа с курсором
// clear_all_line.c - чистка команды
// user_in - массив положения курсора [положение столбца начинается от 0][положение строки начинается от 0]
// str_n(void) - возвращает количество строк занимаемых командой
// rp() - получение статической структуры позиции курсора

static int	is_first_word(char *user_in, int i)
{
	if (user_in[i] == '\0')
		i--;
	while (is_print(user_in[i]) && i && user_in[i] != ' ')
		i--;
	if (!i)
		return (1);
	while ((user_in[i] == ' ' || user_in[i] == '\t' || \
		rp(NULL)->user_in[i] == '\n') && i)
		i--;
	if (!i)
		return (1);
	return (0);
}

void		completion(void)
{
	char			*remainder_word;
	t_completion	*com_lst; //связный список из всех возможных вариатов в данной дире
	t_completion	*matches; //связный список из вариантов подстановок по одной части слова
	char			*path;
	int				i;

	// return ; //lol
	i = search_index(); //получение индекса нахождения курсора из массива user_in
	path = NULL;
	if (!(remainder_word = tab_cut_word(i)))
		return ;
	// is_first_word(i) 1 = first word
	// ft_printf("\n%d", is_first_word(i));
	// ft_printf("\n!%s!", remainder_word);
	// while(1);
	if (is_first_word(rp(NULL)->user_in, i) && !ft_strchr(remainder_word, '/'))
	{
		// while (1);
		com_lst = add_files_path_env();
	}
	else if (!ft_strchr(remainder_word, '/'))
		com_lst = ret_possible_matches(NULL, 0);
	else
	{
		path = return_path(remainder_word);
		com_lst = ret_possible_matches(path, is_first_word(rp(NULL)->user_in, i));
		free(remainder_word);
		remainder_word = cut_word('/', i);
	}
	matches = ret_matches(com_lst, remainder_word);
	if (matches)
		complete_word(matches, remainder_word, path);
	free_completion(com_lst, matches, remainder_word, path);
}
