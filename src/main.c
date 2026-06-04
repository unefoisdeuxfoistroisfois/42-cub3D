/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:19:39 by sariee            #+#    #+#             */
/*   Updated: 2026/06/04 18:48:28 by sariee           ###   ########.fr       */
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
    ft_bzero(&game, sizeof(t_game)); // AJOUT : init tout a zero
    ft_args(argv[1], &game.maps);    // MODIFIE : passe game.maps
	ft_init_player(&game);   		 // AJOUT
    ft_mlx(&game);                   // MODIFIE : passe game 
    return (0);
}
