#include "21sh.h"

/*
** Ищет последнюю позицию курсора по ширине для
** актуальной позиции курсора по высоте (rp()->cur_pos[1]).
*/

int         search_last_cur_pos_in_line(void)
{
    int z;
    int p;
    int y;
    int cur_pos_col;

    z = 1;
    p = 0;
    cur_pos_col = 3;
    while (z != rp()->cur_pos[1])
    {
        if (rp()->user_in[p] == '\n' || cur_pos_col > rp()->ws_col)
        {
            cur_pos_col = 0;
            z++;
        }
        cur_pos_col++;
        p++;
    }
    y = 0;
    cur_pos_col = 1;
    if (rp()->cur_pos[1] == 1)
        cur_pos_col = 3;
    while (rp()->user_in[p] != '\n' && cur_pos_col < rp()->ws_col - 1 && \
        rp()->user_in[p])
    {
        cur_pos_col++;
        p++;
        y++;
    }
    if (rp()->user_in[p] == '\n')
        cur_pos_col--;
    return (cur_pos_col);
}

/*
** Записывает в указатель cur_pos позицию
** курсора после вывода строки (rp()->user_in).
*/

void        cur_pos_after_putstr(int *cur_pos)
{
    int i;
    int n;
    int cur_pos_col;

    cur_pos[1] = str_n() + 1;
    //if (cur_pos[1] == 2)
    //    printf("YES\n");
    if (cur_pos[1] == 1)
    {
        cur_pos[0] = ft_strlen(rp()->user_in) + 3;
        //if (cur_pos[0] - 1 == rp()->ws_col)
        //    cur_pos[0]++;
    }
    else
    {
        i = 0;
        n = cur_pos[1] - 1;
        cur_pos_col = 3;
        while (n)
        {
            if (rp()->user_in[i] == '\n' || cur_pos_col >= rp()->ws_col)
            {
                cur_pos_col = 0;
                n--;
            }
            cur_pos_col++;
            i++;
        }
        cur_pos[0] = 1;
        while (rp()->user_in[i++])
            cur_pos[0]++;
    }
    //if (cur_pos[1] > 1)
    //    printf("cur_pos[0] = %d, cur_pos[1] = %d\n", cur_pos[0], cur_pos[1]);
}
