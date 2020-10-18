/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/10/18 18:24:59 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

// termcap_api.c - работа с курсором
// clear_all_line.c - чистка команды
// user_in - ввод
// str_n(void) - возвращает количество строк занимаемых командой
// rp() - получение статической структуры позиции курсора

int			check_arrow_amper(char *user_in, int i)
{
	if (user_in[i] == '\0')
		i--;
	while (i && user_in[i] != ' ' && user_in[i] != '\t' && \
		user_in[i] != '&')
		i--;
	if (i && user_in[i] == '&' && user_in[i - 1] == '>')
		return (0);
	return (1);
}

int			check_space_or_tab(char *user_in, int i)
{
	if (user_in[i] == ' ' || user_in[i] == '\t')
		return (1);
	return (0);
}

int			check_first_word(char *user_in, int i)
{
	int		j;

	j = 0;
	if (!ft_strlen(user_in))
		return (1);
	else if (!check_arrow_amper(user_in, i))
		return (0);
	while (check_space_or_tab(user_in, j))
		j++;
	// while(1);
	while (j < i)
	{
		if (check_space_or_tab(user_in, j)
			&& j == i)
		{
			while (!check_space_or_tab(user_in, i) && \
				user_in[i] != '&')
			{
				i--;
			}
			if (i > 0 && user_in[i] == '&' && user_in[i - 1] == '>')
				return (0);
			return (1);
		}
		else if (check_space_or_tab(user_in, j))
			return (0);
		j++;
	}
		// while (1);
	return (1);
}

int			tab_check_special_symbols(char *user_in, int j)
{
	if (j > 0 && (user_in[j]  == '|' || (user_in[j] == '&' && \
		user_in[j - 1] != '>')))
	{
		return (1);
	}
	return (0);
}

static int	is_first_word(char *user_in, int i)
{
	int		j;

	j = i;
	if (check_first_word(user_in, i))
	{
		return (1);
	}
	// while (j >= 0 && user_in[j] != '|' && user_in[j] != '&')
	while (j > 0 && !tab_check_special_symbols(user_in, j))
	{
		if (user_in[j] == '&' && user_in[j - 1] == '>')
			return (0);
		// write(1, "t", 1);
		j--;
	}
	if (j >= 0 && (user_in[j] == '|' || user_in[j] == '&'))
	{
		while (check_space_or_tab(user_in, i) || \
			user_in[j] == '|' || user_in[j] == '&')
			j++;
		// while (1);
			// j++;
		while (j < i)
		{
			if ((check_space_or_tab(user_in, i) || user_in[j] == '|' \
				|| user_in[j] == '\0' || user_in[j] == '&') && j == i)
				return (2);
			else if (check_space_or_tab(user_in, i) \
				|| user_in[j] == '\0')
				return (0);
			// ft_printf("\n%d %d", j, i);
			// while (1);
			j++;
		}
		return (2);
	}
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
	i = search_index(); //получение индекса нахождения курсора из массива
	path = NULL;
	if (!(remainder_word = tab_cut_word(rp(NULL)->user_in, i)))
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
		remainder_word = tab_cut_word(rp(NULL)->user_in, i);
	}
	matches = ret_matches(com_lst, &remainder_word);
	if (matches)
	{
		// while (1);
		complete_word(matches, remainder_word, path);
	}
	
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
