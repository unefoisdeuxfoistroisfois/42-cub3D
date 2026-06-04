/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:03:36 by sariee            #+#    #+#             */
/*   Updated: 2026/06/04 19:43:16 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialisation des textures pour chaque direction.
void	ft_init_textures(t_game *game)
{
	// direction N
	game->tex_no.img = mlx_xpm_file_to_image(game->tex_no.mlx, game->maps.path_no, game->tex_no.width, game->tex_no.height); // on charge l'image depuis le fichier.
	game->tex_no.addr = mlx_get_data_addr(); // on recupere l'adresse du buffer de pixels.
	// direction S
	game->tex_so.img = mlx_xpm_file_to_image(game->tex_no.mlx, game->maps.path_no, game->tex_no.width, game->tex_no.height);
	game->tex_so.addr = mlx_get_data_addr(); 
	// direction E
	game->tex_ea.img = mlx_xpm_file_to_image(game->tex_no.mlx, game->maps.path_no, game->tex_no.width, game->tex_no.height);
	game->tex_ea.addr = mlx_get_data_addr(); 
	// diection W
	game->tex_we.img = mlx_xpm_file_to_image(game->tex_no.mlx, game->maps.path_no, game->tex_no.width, game->tex_no.height);
	game->tex_we.addr = mlx_get_data_addr(); 
}