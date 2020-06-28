/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gayprompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:56:16 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 13:56:18 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include <unistd.h>
#include "libft.h"

static int	next_rnd(void)
{
	static int			tmp;

	tmp++;
	return (tmp % 7);
}

int			update_gaymode(int need_update, int new_value)
{
	static int	gaymode = 1;

	if (need_update)
		gaymode = new_value;
	return (gaymode);
}

void		gayprompt(char *prompt)
{
	static char	*colors[] = {KNRM, KRED, KYEL, KGRN, KCYN, KBLU, KMAG};
	int			i;
	int			cur_color;

	if (!prompt)
		return ;
	i = -1;
	while (prompt[++i])
	{
		if (update_gaymode(0, 0))
		{
			cur_color = next_rnd();
			ft_putstr_fd(colors[cur_color], 2);
		}
		write(2, prompt + i, 1);
	}
	if (update_gaymode(0, 0))
		write(2, KNRM, sizeof(KNRM));
}
