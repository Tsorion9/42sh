/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_void_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:08:50 by bgian             #+#    #+#             */
/*   Updated: 2019/12/24 15:14:03 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		swap(void **a, void **b)
{
	void	*c;

	c = *a;
	*a = *b;
	*b = c;
}

/*
**	Median of first, last, mid
**	Orger relation is supposed to be transitive here
*/

static void		**choose_pivot(void **arr, int len,\
		int (*is_greater)(void *, void *))
{
	int	a_b;
	int	b_c;
	int	a_c;

	a_b = is_greater(*arr, *(arr + len / 2));
	b_c = is_greater(*(arr + len / 2), *(arr + len - 1));
	a_c = is_greater(*arr, *(arr + len - 1));
	if (a_b >= 0 && b_c >= 0)
		return (arr + len / 2);
	if (a_c >= 0 && b_c <= 0)
		return (arr + len - 1);
	return (arr);
}

static void		**place_pivot(void **arr, int len,\
		int (*is_greater)(void *, void *), void **pivot)
{
	int		i;
	int		n_below_pivot;

	n_below_pivot = 0;
	i = 0;
	swap(pivot, arr + len - 1);
	pivot = arr + len - 1;
	while (i < len)
	{
		if (is_greater(*pivot, *(arr + i)) > 0)
			swap(arr + n_below_pivot++, arr + i);
		i++;
	}
	swap(pivot, arr + n_below_pivot);
	pivot = arr + n_below_pivot;
	return (pivot);
}

/*
**	Sort ascending always
**	Cmp returns positive int if first arg is greater
*/

void			qsort_void_ptr(void **arr, int len,\
		int (*is_greater)(void *, void *))
{
	void	**pivot;

	if (len <= 1)
		return ;
	pivot = choose_pivot(arr, len, is_greater);
	pivot = place_pivot(arr, len, is_greater, pivot);
	if (pivot - arr)
		qsort_void_ptr(arr, pivot - arr, is_greater);
	if (pivot - arr < len - 1)
		qsort_void_ptr(pivot + 1, arr + len - 1 - pivot, is_greater);
}
