#include "cub3d.h"

int	ft_clean(t_data *data)
{
    if (data->img)
    {
        mlx_destroy_image(data->mlx, data->img);
    }
    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
    }
    if (data->mlx)
    {
        free(data->mlx);
    }
    printf("You left\n");
    exit(0);
    return (0);
}