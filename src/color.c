#include "cub3d.h"

void    ft_valide_colors(char *line)
{
    char    **ressplit;
    int resatoi;
    int i;

    ressplit = ft_split(line, ',');
    i = 0;
    while (ressplit[i] != NULL)
    {
        resatoi = ft_atoi(ressplit[i]);
        if (resatoi < 0 || resatoi > 255)
        {
            printf ("Les données des couleurs sont trop grand ou trop petit");
            exit(EXIT_FAILURE);
        }
        printf ("%d ", resatoi);
        i ++;
    }
    if (i != 3)
    {
        printf ("Erreur il faut au moin 3 valeur");
        exit(EXIT_FAILURE);
    }
    printf ("\n");
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

void    ft_check_colors(char *line)
{
    char *resstrcolors;

    if (ft_strncmp(line, "F", 1) == 0)
    {
        resstrcolors = ft_strcolors(line);
        ft_valide_colors(resstrcolors);
    }
    if (ft_strncmp(line, "C", 1) == 0)
    {
        resstrcolors = ft_strcolors(line);
        ft_valide_colors(resstrcolors);
    }
}

/*
    1. Verifier F et C dans notre chaine
    2. utilisé split pour séparé ','
    3. atoi pour avoir des int.
    4. verifier que c'est entre 0 et 255.
*/