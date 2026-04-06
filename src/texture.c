#include "cub3d.h"

void    ft_check_texture(char *line)
{
    if (ft_strncmp(line, "NO", 2))
    {
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(line, "SO", 2) != 0)
    {
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(line, "WE", 2) != 0)
    {
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(line, "EA", 2) != 0)
    {
        exit(EXIT_FAILURE);
    }
}