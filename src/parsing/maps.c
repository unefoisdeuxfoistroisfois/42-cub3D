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

/**
 * on entre le premier element
 * ensuite 
 */
void    ft_add_line(char *line, t_maps *maps)
{
    int size;
    char **newmap;

    // si NULL (premiere ligne) a copié
    if (maps->map == NULL)
    {
        maps->map = malloc(sizeof(char *) * 2);
        maps->map[0] = ft_strdup(line);
        maps->map[1] = NULL; // pour quitté la boucle
        printf ("Premiere ligne stocké : %s", maps->map[0]);
    }
    else
    {
        // calcul la taille poru une nouveau malloc car on peux pas malloc 2 fois
        size = 0;
        while (maps->map[size] != NULL)
        {
            size ++;
        }
        //la taille acutel de se que contien maps->map * (la nouvelle ligne + NULL)
        newmap = malloc(sizeof(char * ) *(size + 2));

        // copie notre char ** dans le newmaps car on peu pas malloc 2 feu
        size = 0;
        while (maps->map[size] != NULL)
        {
            newmap[size] = maps->map[size];
            size ++;
        }

        newmap[size] = ft_strdup(line);
        newmap[size + 1] = NULL;
        free(maps->map);

        // Comme c'est un ** alros on peux faire un réaffecation vers l'afresse de newmap
        maps->map = newmap;
    }
}

// regard ligne par ligne.
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
        // Si il y'a aucun caractere étranger alors onpeux la stocker.
        ft_add_line(line, maps);
        return (1);
    }
    else
        return (0);
}