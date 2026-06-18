/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:03:36 by sariee            #+#    #+#             */
/*   Updated: 2026/06/16 12:42:45 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_load_tex(t_game *game, t_data *tex, char *path)
{
	// on charge l'image depuis le fichier xpm donc img est juste est juste un pointeur vers cette image en memoire.
	tex->img = mlx_xpm_file_to_image(game->data.mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Erreur chargement texture '%s'\n", path);
		exit(EXIT_FAILURE);
	}
	// on recupere l'adresse du buffer de pixels. Img est opaque donc on ne peut pas lire les pixels directement, la fonction get data addr donne un pointeur vers le début du tableau de pixels.
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

// initialisation des textures pour chaque direction.
void	ft_init_textures(t_game *game)
{
	// Direction NO
	ft_load_tex(game, &game->tex_no, game->maps.path_no);
	// Direction SO
	ft_load_tex(game, &game->tex_so, game->maps.path_so);
	// Direction EA
	ft_load_tex(game, &game->tex_ea, game->maps.path_ea);
	// Direction WE
	ft_load_tex(game, &game->tex_we, game->maps.path_we);
}
