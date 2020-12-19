/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/14 21:37:46 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

// termcap_api.c - работа с курсором
// clear_all_line.c - чистка команды
// user_in - ввод
// str_n(void) - возвращает количество строк занимаемых командой
// rp() - получение статической структуры позиции курсора

void		completion(void)
{
	char			*remainder_word;
	t_completion	*com_lst; //связный список из всех возможных вариатов в данной дире
	t_completion	*matches; //связный список из вариантов подстановок по одной части слова
	char			*path;
	int				i;
	int				com_case;

	com_api_clear_till_end();
	i = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len); //получение индекса нахождения курсора из массива
	com_case = find_complection_pos(rp(NULL)->user_in, i);
	path = NULL;
	// ft_printf("%d", i);
	
	remainder_word = tab_cut_word(rp(NULL)->user_in, i);
	
	// if (!(remainder_word = tab_cut_word(rp(NULL)->user_in, i)))
	// 	return ; //Добавить подстановку всех вариантов при отсутствии слова
		
	// ft_printf("!%s, %d %d!!", rp(NULL)->user_in, i, com_case);
	// is_first_word(i) 1 = first word
	// ft_printf("\n%d", is_first_word(i));
	// ft_printf("\n!%s!", remainder_word);
	// while(1);
	if (com_case == COM_CMD && !ft_strchr(remainder_word, '/'))
	{
		// while (1);
		com_lst = add_files_path_env();
	}
	else if (com_case == COM_FILE && !ft_strchr(remainder_word, '/'))
		com_lst = ret_possible_matches(NULL, 0);
	// else if (com_case == COM_VAR)
	// 	com_lst = ret_possible_vars(NULL, 0);
	else
	{
		// while (1);
		path = return_path(remainder_word);
		com_lst = ret_possible_matches(path, com_case);
		free(remainder_word);
		remainder_word = tab_cut_word(rp(NULL)->user_in, i);
	}
	// ft_printf("\n\n%s\n%s", remainder_word, path);
	matches = ret_matches(com_lst, &remainder_word);
	
	// if (matches)
	// {
	// 	ft_printf("123 %s", matches->str);
	// 	while (1);
	// }
	// com_api_print_output(matches, remainder_word, path);
	com_api_print_suggestion(matches, remainder_word, path);

	// ft_printf("!%d!", comlections_list_len(matches));

	// if (com_lst)
	// {
	// 	ft_printf("%s", com_lst->str);
	// 	// while (1);
	// }
	// com_print_suggestion();
	
	// while (com_lst)
	// {
	// 	ft_printf("\n%s", com_lst->str);
	// 	com_lst = com_lst->next;
	// }
	// while (1);
	// while (matches)
	// {
	// 	ft_printf("\n%s", matches->str);
	// 	matches = matches->next;
	// }
	free_completion(com_lst, matches, remainder_word, path);
}
