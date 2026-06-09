/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:19:39 by sariee            #+#    #+#             */
/*   Updated: 2026/06/09 17:19:04 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        printf("Erreur");
        return (1);
    }
    ft_bzero(&game, sizeof(t_game));	// AJOUT : init tout a zero
    ft_args(argv[1], &game.maps);		// MODIFIE : passe game.maps
	ft_init_mlx(&game);
	ft_init_player(&game);				// init des joueurs
	ft_init_textures(&game);			// init des textures
	ft_init_colors(&game);				// init des couleurs RGB en int
    ft_run_mlx(&game);						// MODIFIE : passe game 
    return (0);
}
