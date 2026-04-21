#include "cub3d.h"

/**
 * Ma ft_neighbors sa verifie que la map est fermee par des murs si 
 * je trouve un 0
 *
 * Parcourt chaque case de la map avec une double boucle.
 * Pour chaque '0' trouve, je verifie que ses 4 voisins
 * (haut, bas, gauche, droite) ne sont pas des espaces.
 * Si un voisin est un espace, le joueur pourrait sortir
 * de la map sa ferrait une erreur.
 *
 * Protection contre les debordements :
 * si i > 0 avant de regarder en haut
 * si maps->map[i + 1] != NULL avant de regarder en bas
 * si j > 0 avant de regarder a gauche
 * si maps->map[i][j + 1] != '\0' avant de regarder a droite
 */
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