#include "cub3d.h"

/* Verifie si on a que un seul caractere N S W E */
void    ft_player(char *line, t_maps *maps)
{
    int i;

    i = 0;
    while (line[i] != '\0' && line[i] != '\n')
    {
        if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'W' || line[i] == 'E')
        {
            // si deja trouvé un joueur
            if (maps->player == 1)
            {
                printf("Il existe deja un joueur, un joueur en trop dans la maps");
                exit(EXIT_FAILURE);
            }
            maps->player = 1;
        }
        i ++;
    }
}

int ft_check_maps(char *line, t_maps *maps)
{
    int i;
    
    if (line [0] == '1' || line [0] == '0' || line[0] == ' ')
    {
        ft_player(line, maps);
        i = 0;
        while (line[i] != '\0' && line[i] != '\n')
        {
            if (line[i] != '0' && line[i] != '1' && line[i] != ' '
                && line[i] != 'N' && line[i] != 'S' 
                && line[i] != 'W' && line[i] != 'E')
            {
                printf("Erreur caractere de la maps pas valide");
                exit(EXIT_FAILURE);
            }
            i ++;
        }
        printf("Aucun caractere etranger dans la linge\n");
        return (1);
    }
    else
        return (0);
}