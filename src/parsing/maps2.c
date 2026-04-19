#include "cub3d.h"

int ft_strlen_maps(t_maps *maps)
{
    int size;

    size = 0;
    while (maps->map[size] != NULL)
    {
        size ++;
    }
    return (size);
}

void    ft_check_left_right_side(t_maps *maps)
{
    int i;
    int j;
    int sizemap;

    i = 0;
    sizemap = ft_strlen_maps(maps);
    while (i < sizemap)
    {
        // sauté les espace car il contient pas de 1
        j = 0;
        while ((maps->map[i][j] >= 9 && maps->map[i][j] <= 13)
            || maps->map[i][j] == ' ')
        {
            j ++;
        }
        if (maps->map[i][j] != '1')
        {
            printf("Erreur : Bord gauche pas bon [%d] [%d]", i, j);
            exit(EXIT_FAILURE);
        }
        // strlen de chaque ligne 
        j = ft_strlen(maps->map[i]) - 1;
        while ((maps->map[i][j] >= 9 && maps->map[i][j] <= 13)
            || maps->map[i][j] == ' ')
        {
            j --;
        }
        if (maps->map[i][j] != '1')
        {
            printf("Erreur : Bord droit pas bon [%d] [%d]", i, j);
            exit(EXIT_FAILURE);
        }
        i ++;
    }
    printf("OK les coté on que des 1");
}

void    ft_check_first_last_line(t_maps *maps)
{
    int i;
    int sizemap;

    i = 0;
    sizemap = ft_strlen_maps(maps);

    // Premier ligne
    while (maps->map[0][i] != '\0' && maps->map[0][i] !=  '\n')
    {
        if (maps->map[0][i] != '1' 
            && maps->map[0][i] != ' '
            && !(maps->map[0][i] >= 9 && maps->map[0][i] <= 13))
        {
            printf("Erreur : la premiere ligne invalide\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Derniere ligne
    i = 0;
    while (maps->map[sizemap - 1][i] != '\0' && maps->map[sizemap - 1][i] !=  '\n')
    {
        if (maps->map[sizemap - 1][i] != '1' 
            && maps->map[sizemap - 1][i] != ' '
            && !(maps->map[sizemap - 1][i] >= 9 && maps->map[sizemap - 1][i] <= 13))

        {
            printf("Erreur : la dernier ligne invalide\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    printf("Premier et dernier ligne ok ils ont que des 1\n");
}