#include "cub3d.h"

/*
int    ft_line(char *str)
{
    int fd;
    char *line;

    printf ("Choix : %s\n", str);
    fd  = open(str, O_RDONLY);
    if (fd < 0)
    {
        printf("Ne peut pas ouvrir");
        return (-1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        // Traitement de la ligne
        free(line);
    }
    close (fd); 
    return (0);
} */

int    ft_is_dot_cub(char *str)
{
    char * dot;
    int resstrcmp;

    // strchr retourn un NULL;
    dot = ft_strchr (str, '.');
    resstrcmp = ft_strncmp(dot, ".cub", 4);
    if (dot == NULL || resstrcmp != 0)
    {
        return (0);
    }
    return (1);
}

void    ft_args(char *str)
{
    int res;
    // verif si c'est un .dot
    res = ft_is_dot_cub(str);
    if (res == 0)
    {
        printf("Le fichier doit avoir un .cub\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Le fichier est bon\n");
        exit(EXIT_SUCCESS);
    }
}