/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 23:45:57 by sariee            #+#    #+#             */
/*   Updated: 2026/06/16 12:41:14 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Rotation du joueur avec les fleches gauche et droite.
// On applique une matrice de rotation 2D sur dir et plane.
// Matrice de rotation 2D pour un angle rot :
//   new_x = x * cos(rot) - y * sin(rot)
//   new_y = x * sin(rot) + y * cos(rot)
void	ft_rotate_player(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = 0;
	if (keycode == LEFT || keycode == LEFT_MAC) // fleche gauche
		rot = -ROT_SPEED;
	if (keycode == RIGHT || keycode == RIGHT_MAC) // fleche droite
		rot = ROT_SPEED;
	if (rot == 0)
		return ;
	// rotation du vecteur direction
	// old_dir_x sauvegarde car dir_x est ecrase avant d'etre utilise pour dir_y
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos(rot) - game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	// rotation du plan camera (FOV) — meme matrice, meme logique de sauvegarde
	// le plan camera doit toujours rester perpendiculaire a dir
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos(rot) - game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot) + game->player.plane_y * cos(rot);
}

// Meme principe que ft_rotate_player, mais l'angle de rotation est recu
// directement en parametre au lieu d'etre deduit d'une touche.
// Utilisee pour la rotation a la souris (ft_mouse), ou l'angle depend
// de la distance entre la souris et le centre de l'ecran.
void   	ft_rotate_angle(double rot, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (rot == 0)
		return ;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos(rot) - game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos(rot) - game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot) + game->player.plane_y * cos(rot);
}
