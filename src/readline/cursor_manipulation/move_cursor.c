#include "21sh.h"

/*
** Перемещает курсор на одну позицию влево.
*/

static void	move_cursor_left(void)
{
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp()->cur_pos[0];
	prev_cur_pos[1] = rp()->cur_pos[1];
	if (rp()->cur_pos[0] == 1)
	{
		rp()->cur_pos[1]--;
		rp()->cur_pos[0] = search_last_cur_pos_in_line() + 1;
		//printf("%d\n", rp()->cur_pos[0]);
	}
	else if (rp()->cur_pos[0] == 3 && rp()->cur_pos[1] == 1)
		return ;
	else
		rp()->cur_pos[0]--;
	ret_cur_to_original_pos(prev_cur_pos);
}

/*
** Перемещает курсор на одну позицию вправо.
*/

static void move_cursor_right(void)
{
	int	i;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp()->cur_pos[0];
	prev_cur_pos[1] = rp()->cur_pos[1];
	i = search_index();
	if (rp()->user_in[i] == '\n' || rp()->cur_pos[0] == rp()->ws_col)
	{
		rp()->cur_pos[0] = 1;
		rp()->cur_pos[1]++;
		//printf("rp()->cur_pos[0] = %d, rp()->cur_pos[1] = %d\n", rp()->cur_pos[0], rp()->cur_pos[1]);
	}
	else if (rp()->user_in[i] != 0)
		rp()->cur_pos[0]++;
	//else
	//	printf("rp()->cur_pos[0] = %d, rp()->cur_pos[1] = %d\n", rp()->cur_pos[0], rp()->cur_pos[1]);
	ret_cur_to_original_pos(prev_cur_pos);
}

/*
** Перемещает курсор на одну позицию.
*/

void        move_cursor(long c)
{
	if (c == LEFT_ARROW)
		move_cursor_left();
	else
		move_cursor_right();
}
