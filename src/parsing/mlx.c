/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:34:43 by sariee            #+#    #+#             */
/*   Updated: 2026/06/04 15:34:50 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// MODIFIE : t_game *game au lieu de void **mlx_connection, void **mlx_window, t_data *data
void	ft_init_mlx(t_game *game)
{
	// La connexion avec le système graphique, qui retourne un pointeur *mlx
	game->data.mlx = mlx_init(); // MODIFIE : *mlx_connection = mlx_init()
	// Crée une fenêtre de la taille donnée avec un titre.
	game->data.win = mlx_new_window(game->data.mlx, WIDTH, HEIGHT, "cub3D"); // MODIFIE
	// Crée une image en mémoire (le buffer où on vas dessiner).
	game->data.img = mlx_new_image(game->data.mlx, WIDTH, HEIGHT); // MODIFIE
	// Récupère l'adresse du buffer de l'image pour pouvoir écrire dedans pixel par pixel
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel,
			&game->data.line_length, &game->data.endian); // MODIFIE
}

// MODIFIE : t_game *game au lieu de void *mlx_connection, void *mlx_window, t_data *data
void	ft_run_mlx(t_game *game)
{
	mlx_key_hook(game->data.win, ft_key, game); // MODIFIE
	mlx_hook(game->data.win, 17, 0, ft_clean, game); // MODIFIE : peux quitter le programme avec la croix
	// envoie l'image du buffer vers la fenêtre pour l'afficher.
	mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img, 0, 0); // MODIFIE
	// Lance la boucle infinie
	mlx_loop(game->data.mlx); // MODIFIE
}

// MODIFIE : t_game *game au lieu de void, variables locales supprimees
void	ft_mlx(t_game *game)
{
	ft_init_mlx(game); // MODIFIE
	ft_run_mlx(game);  // MODIFIE
}
