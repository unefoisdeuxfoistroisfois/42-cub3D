#include "cub3d.h"

void    ft_neighbors(t_maps *maps)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (maps->map[i] != NULL)
    {
        j = 0;
        while (maps->map[i][j] != '\0' && maps->map[i][j] != '\n')
        {
            if (maps->map[i][j] == '0')
            {
                // verifie que on est pas sur la premiere ligne avant de regarder i - 1
                if (i > 0  && maps->map[i - 1][j] == ' ')  //Regard en haut
                {
                    printf("Error\nMap pas fermee [%d][%d] haut\n", i, j);
                    exit(EXIT_FAILURE);
                }
                // verifie si il y'a une ligne en dessous
                if (maps->map[i + 1] != NULL && maps->map[i + 1][j] == ' ')  // Regard en bas
                {
                    printf("Error\nMap pas fermee [%d][%d] bas\n", i, j);
                    exit(EXIT_FAILURE);
                }
                // verifie que on est pas au debut de la ligne avant de regarder
                if (j > 0 && maps->map[i][j - 1] == ' ')  // gauche
                {
                    printf("Error\nMap pas fermee [%d][%d] gauche\n", i, j);
                    exit(EXIT_FAILURE);
                }
                // verifier que il y'a un caracter a droite avant de regarder
                if (maps->map[i][j + 1] != '\0'  && maps->map[i][j + 1] == ' ')  // droite
                {
                    printf("Error\nMap pas fermee [%d][%d] droite\n", i, j);
                    exit(EXIT_FAILURE);
                }
            }
            j ++;
        }
        i ++;
    }
    printf("Map fermee par des murs OK\n");
}