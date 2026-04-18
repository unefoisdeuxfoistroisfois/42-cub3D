#include "cub3d.h"

void    ft_check_first_last_line(t_maps *maps)
{
    int i;

    i = 0;
    while (maps->map[1][i] != '\0')
    {
        if (maps->map[i] != 1)
            exit(EXIT_FAILURE);
    }
    return ;

}