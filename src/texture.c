#include "cub3d.h"

// retourne 0 quand c'eest ok
void    ft_check_texture(char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
    {
        printf("Texture Nord : %s\n", line + 3);
    }
    if (ft_strncmp(line, "SO", 2) == 0)
    {
        printf("Texture Sud : %s\n", line + 3);
    }
    if (ft_strncmp(line, "WE", 2) == 0)
    {
        printf("Texture Ouest : %s\n", line + 3);
    }
    if (ft_strncmp(line, "EA", 2) == 0)
    {
        printf("Texture Est : %s\n", line + 3);
    }
}