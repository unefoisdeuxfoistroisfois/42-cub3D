/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:44:15 by sariee            #+#    #+#             */
/*   Updated: 2026/06/16 13:30:30 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_game *game, int x, int y, int color)
{
	char    *dst;

	dst = game->data.addr + (y * game->data.line_length + x * (game->data.bits_per_pixel / 8));
	// je cast dst `(unsigned int *)dst` pour qu'il traite dst comme un pointeur vers 4 bytes au lieu de 1 byte
	// ensuite je rajoute le pointeur `*(unsignmed int*)dst devant la paranthese pour qu'il ecrit les 4 bytes d'un coup
	*(unsigned int *)dst = color;
}

// ici je met a jour le jeu a chaque frame
// verification de l'etat de chaque touche si je les maintient ou non
// et j'applique le mouvement ou rotation correspondante, ensuite je relance le raycaster
// pour redessiner l'image avec la nouvelle poisition ou direction du joueur
// `[0 a 3]` = `W/S/A/D`, `[4 et 5]` = les fleches `gauche` et `droite`
int	ft_render(t_game *game)
{
	if (game->keys[0])
		ft_move_player_w(game);
	if (game->keys[1])
		ft_move_player_s(game);
	if (game->keys[2])
		ft_move_player_a(game);
	if (game->keys[3])
		ft_move_player_d(game);
	if (game->keys[4])
		ft_rotate_player(LEFT, game);
	if (game->keys[5])
		ft_rotate_player(RIGHT, game);
	ft_raycaster(game);
	ft_draw_minimap(game);  // AJOUT
	// envoie l'image redessinee vers la fenetre
	mlx_put_image_to_window(game->data.mlx, game->data.win, game->data.img, 0, 0);
	return (0);
}
