/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/10/17 11:09:06 by alexbuyanov      ###   ########.fr       */
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
	int		j;

	j = 0;
	if (!ft_strlen(user_in))
		return (1);
	while (user_in[j] == ' ' || user_in[j] == '\t')
		j++;
	while (j < i)
	{
		if ((user_in[j] == '\t' || user_in[j] == ' ')
			&& j == i)
			return (1);
		else if ((user_in[j] == '\t' || user_in[j] == ' '))
			return (0);
		j++;
	}
	return (1);
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
	if (!(remainder_word = tab_cut_word(rp(NULL)->user_in, i)))
		return ;
	// is_first_word(i) 1 = first word
	// ft_printf("\n%d", is_first_word(i));
	// ft_printf("\n!%s!", remainder_word);
	// while(1);
	if (is_first_word(rp(NULL)->user_in, i) && !ft_strchr(remainder_word, '/'))
	{
		while (1);
		com_lst = add_files_path_env();
	}
	else if (!ft_strchr(remainder_word, '/'))
		com_lst = ret_possible_matches(NULL, 0);
	else
	{
		path = return_path(remainder_word);
		com_lst = ret_possible_matches(path, is_first_word(rp(NULL)->user_in, i));
		free(remainder_word);
		remainder_word = tab_cut_word(rp(NULL)->user_in, i);
	}
	matches = ret_matches(com_lst, remainder_word);
	if (matches)
		complete_word(matches, remainder_word, path);
	
	// while (com_lst)
	// {
	// 	ft_printf("\n%s", com_lst->str);
	// 	com_lst = com_lst->next;
	// }
	
	// while (matches)
	// {
	// 	ft_printf("\n%s", matches->str);
	// 	matches = matches->next;
	// }
	free_completion(com_lst, matches, remainder_word, path);
}
