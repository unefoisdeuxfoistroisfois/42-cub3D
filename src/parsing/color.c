#include "cub3d.h"

// SAM Ajout de int *rgb en parametre pour stocker les valeurs
void    ft_valide_colors(char *line, int *rgb)
{
    char    **ressplit;
    int     resatoi;
    int     i;

    ressplit = ft_split(line, ',');
    i = 0;
    while (ressplit[i] != NULL)
    {
        resatoi = ft_atoi(ressplit[i]);
        if (resatoi < 0 || resatoi > 255)
        {
            printf("Les données des couleurs sont trop grand ou trop petit");
            exit(EXIT_FAILURE);
        }
        rgb[i] = resatoi; // AJOUT : stockage de la valeur RGB
        i++;
    }
    if (i != 3)
    {
        printf("Erreur il faut au moin 3 valeur");
        exit(EXIT_FAILURE);
    }
}

char    *ft_strcolors(char *line)
{
    char *res;
    char *trimmed;

    res = ft_strchr(line, ' ');
    if (res == NULL)
    {
        printf("pas bon");
        exit(EXIT_FAILURE);
    }
    else
    {
        res = res + 1;
    }
    trimmed = ft_strtrim(res, "\n");

    return (trimmed);
}

// SAM Ajout de t_maps *maps en parametre + stockage des couleurs
void    ft_check_colors(char *line, t_maps *maps)
{
    char *resstrcolors;

    if (ft_strncmp(line, "F", 1) == 0)
    {
        resstrcolors = ft_strcolors(line);
        ft_valide_colors(resstrcolors, maps->floor); // AJOUT : passe maps->floor
    }
    if (ft_strncmp(line, "C", 1) == 0)
    {
        resstrcolors = ft_strcolors(line);
        ft_valide_colors(resstrcolors, maps->ceil); // AJOUT : passe maps->ceil
    }
}

/*
    1. Verifier F et C dans notre chaine
    2. utilisé split pour séparé ','
    3. atoi pour avoir des int.
    4. verifier que c'est entre 0 et 255.
*/
