#include "cub3d.h"

int ft_key(int keycode, t_data *data)
{
    if (keycode == 65307 || keycode == 53) // ESC
    {
        ft_clean(data);
        return (0);
    }
    if (keycode == 13 || keycode == 119) // W
        printf("W\n");
    if (keycode == 0 || keycode == 97) // A
        printf("A\n");
    if (keycode == 1 || keycode == 115) // S
        printf("S\n");
    if (keycode == 2 || keycode == 100) // D
        printf("D\n");
    if (keycode == 123 || keycode == 65361) // fleche gauche
        printf("Gauche\n");
    if (keycode == 124 || keycode == 65363) // fleche droite
        printf("Droite\n");
    return (0);
}