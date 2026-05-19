#include "cub3d.h"

int    main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        printf("Erreur");
        return (1);
    }
    ft_bzero(&game, sizeof(t_game)); // AJOUT : init tout a zero
    ft_args(argv[1], &game.maps);    // MODIFIE : passe game.maps
    ft_mlx(&game);                   // MODIFIE : passe game
    return (0);
}
