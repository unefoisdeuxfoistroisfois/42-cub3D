#include "cub3d.h"

void    ft_flags(char *line, t_maps *maps)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        maps->no = 1;
    }
    if (ft_strncmp(line, "SO ", 3) == 0)
    {
        maps->so = 1;
    }
    if (ft_strncmp(line, "WE ", 3) == 0)
    {
        maps->we = 1;
    }
    if (ft_strncmp(line, "EA ", 3) == 0)
    {
        maps->ea = 1;
    }
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        maps->f = 1;
    }
    if (ft_strncmp(line, "C ", 2) == 0)
    {
        maps->c = 1;
    }
}

// Traitement de la ligne
int    ft_line(char *str)
{
    int fd;
    char *line;
    t_maps  maps;

    ft_bzero(&maps, sizeof(t_maps));
    printf ("Choix : %s\n", str);
    fd  = open(str, O_RDONLY);
    if (fd < 0)
    {
        printf("Ne peut pas ouvrir le fichier");
        return (-1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] != '\n' && line[0] != '\0')
        {
            ft_flags(line, &maps);
            ft_check_texture(line);
            ft_check_colors(line);
            ft_check_maps(line, &maps);
        }
        else
            free (line);
    }
    close (fd); 
    ft_check_first_last_line(&maps);
    ft_check_left_right_side(&maps);
    if (maps.no == 0 || maps.so == 0 || maps.we == 0 || maps.ea == 0 
        || maps.f == 0 || maps.c == 0)
    {
        printf("Erreur il manque des elements dans la maps");
        exit(EXIT_FAILURE);
    }
    if (maps.player == 0)
    {
        printf ("Pas de joueur");
        exit(EXIT_FAILURE);
    }
    if (maps.player == 1)
    {
        printf ("Un seul joueur c'est OK");
    }

    if (maps.map != NULL)
    {
        int i = 0;
        while (maps.map[i] != NULL)
        {
            printf("map[%d] = %s", i, maps.map[i]);
            i ++;
        }
    }

    return (0);
}

int    ft_is_dot_cub(char *str)
{
    char * dotcub;
    int resstrcmp;

    // strchr retourn un NULL;
    dotcub = ft_strchr (str, '.');
    if (dotcub == NULL)
    {
        return (0);
    }
    resstrcmp = ft_strncmp(dotcub, ".cub", 4);
    if (resstrcmp != 0)
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
        printf("Le fichier .cub est bon\n");
        ft_line(str);
    }
}