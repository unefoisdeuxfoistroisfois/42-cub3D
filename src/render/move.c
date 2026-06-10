/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:36:37 by sariee            #+#    #+#             */
/*   Updated: 2026/06/10 18:29:32 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// deplacement du joueur en fonction de la touche pressee
// on calcule sa nouvelle position puis on verifie si cette nouvelle position n'est pas dans un mur `1`
// si ce n'est pas un mur on applique le changement et on deplace le joueur, sinon on ne bouge pas 
void	ft_move_player_WS(int keycode, t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	// dir_x et dir_y forment le vecteur de direction du joueur `ex: nord = (0, -1)`
	// on multiplie la pos et dir par la vitesse de deplacement
	if (keycode == W || keycode == W_MAC) // avance
	{
		new_pos_x = game->player.pos_x + game->player.dir_x * SPEED;
		new_pos_y = game->player.pos_y + game->player.dir_y * SPEED;
		if (game->maps.map[(int)new_pos_y][(int)new_pos_x] != '1')	// on cast la nouvelle position pour bien comparer a `1` en int
		{
			game->player.pos_x = new_pos_x;
			game->player.pos_y = new_pos_y;
		}
		printf("W\n");
	}
	// juste ici on soustrait vu que c'est pour aller dans la direction opposee
	if (keycode == S || keycode == S_MAC) // recule
	{
		new_pos_x = game->player.pos_x - game->player.dir_x * SPEED;
		new_pos_y = game->player.pos_y - game->player.dir_y * SPEED;
		if (game->maps.map[(int)new_pos_y][(int)new_pos_x] != '1')
		{
			game->player.pos_x = new_pos_x;
			game->player.pos_y = new_pos_y;
		}
		printf("S\n");
	}
}

void	ft_move_player_AD(int keycode, t_game *game)
{
	double	new_pos_x;
	double	new_pos_y;

	if (keycode == A || keycode == A_MAC) // deplacement sur la gauche
	{
		new_pos_x = game->player.pos_x - game->player.dir_y * SPEED;
		new_pos_y = game->player.pos_y + game->player.dir_x * SPEED;
		if (game->maps.map[(int)new_pos_y][(int)new_pos_x] != '1')
		{
			game->player.pos_x = new_pos_x;
			game->player.pos_y = new_pos_y;
		}
		printf("A\n");
	}
	if (keycode == D || keycode == D_MAC) // deplacement sur la droite
	{
		new_pos_x = game->player.pos_x + game->player.dir_y * SPEED;
		new_pos_y = game->player.pos_y - game->player.dir_x * SPEED;
		if (game->maps.map[(int)new_pos_y][(int)new_pos_x] != '1')
		{
			game->player.pos_x = new_pos_x;
			game->player.pos_y = new_pos_y;
		}
		printf("D\n");
	}
}

void	ft_rotate_player(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = 0;
	if (keycode == LEFT || keycode == LEFT_MAC) // fleche gauche
	rot = ROT_SPEED;
	if (keycode == RIGHT || keycode == RIGHT_MAC) // fleche droite
		rot = -ROT_SPEED;
	if (rot == 0)
		return ;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos(rot) - game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = old_plane_x * cos(rot) - game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot) + game->player.plane_y * cos(rot);
}
