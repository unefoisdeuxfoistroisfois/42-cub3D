#include "cub3d.h"

// MODIFIE : t_game *game au lieu de t_data *data
int	ft_clean(t_game *game)
{
    if (game->data.img) // MODIFIE : game->data.img
    {
        mlx_destroy_image(game->data.mlx, game->data.img);
    }
    if (game->data.win) // MODIFIE : game->data.win
    {
        mlx_destroy_window(game->data.mlx, game->data.win);
    }
    if (game->data.mlx) // MODIFIE : game->data.mlx
    {
        free(game->data.mlx);
    }
    printf("You left\n");
    exit(0);
    return (0);
}
