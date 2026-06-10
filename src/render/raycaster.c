/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:04:08 by sariee            #+#    #+#             */
/*   Updated: 2026/06/10 14:19:34 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// fonction principale du rendu qui tourne pour chaque frame
// pour chaque colonne x de l'ecran, lance un rayon et dessine la colonne
void    ft_raycaster(t_game *game)
{
    int     x;
	int		y;
	int		side;
	int		map_x;
	int		map_y;
	int 	step_x;
	int 	step_y;
    double  camera_x;
	int		draw_end;
    double  ray_dir_x;
    double  ray_dir_y;
	int		draw_start;
	int		line_height;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;

    x = 0;
	// on va parcourir de `x = 0` jusqu'a la limite de `WIDTH`.
    while (x < WIDTH)
    {
		// `camera_x` = la position normalisee de la colonne dans l'ecran : -1 = gauche, 0 = centre, 1 = droite
        camera_x = 2 * x / (double)WIDTH - 1;

		// direction pour cette colonne
		// il faut combiner la direction du joueur avec le plan camera en fonction de `camera_x`
		// et plus `camera_x` est grand, plus le rayon devie vers la droite
        ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
        ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;

		// case de la grille ou se trouver le joueur et vu que pos est une varible `double`
		// `ex : 3.7` bas on le cast en int pour avoir la case `3`
		map_x = (int)game->player.pos_x;
		map_y = (int)game->player.pos_y;

		// c'est la distance que la rayon parcourt entre deux lignes verticales `x` et horizontales `y`
		// constante tout le long du rayon, cela sert a avancer d'une case a la fois 
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);

		// distance jusqu'au premier croisement vertical
		// le joueur est a l'interieur d'une case donc la distance est moins qu'un delta complet
		// step_x nous indique dans quelle direction le rayon avance : `1 = droite, -1 = gauche`
		if (ray_dir_x > 0)
		{
			side_dist_x = (map_x + 1 - game->player.pos_x) * delta_dist_x;
			step_x = 1;
		}
		else
		{
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
			step_x = -1;
		}

		// distance jusqu'au premier croisement horizontale
		// step_y nous indique dans quelle direction le rayon avance : `1 = bas, -1 = haut`
		if (ray_dir_y > 0)
		{
			side_dist_y = (map_y + 1 - game->player.pos_y) * delta_dist_y;
			step_y = 1;
		}
		else
		{
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		    step_y = -1;
		}

		// DDA : on fait avancer le rayon case par case jusqu'a toucher un mur
		// a chaque case passer on choisit le cote le plus proche (veritcal ou horizontal)
		while (game->maps.map[map_y][map_x] != '1')
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;	// avance au prochain croisement vertical
				map_x += step_x;	// passe a la case suivante en `x`
				side = 0;	// `side` = 0 -> un mur vertical a ete toucher (face `N` ou `S`)
			}
			else
			{
				side_dist_y += delta_dist_y;	// avance au prochain croisement horizontal
				map_y += step_y;	// passe a la case suivante en `y`
				side = 1;	// `side` = 1 -> un mur horizontale a ete toucher (face `E` ou `W`)
			}
		}

		// distance perpendiculaire entre le mur et le joueur ce qui nous evite d'avoir l'effet `fish-eye`
		// on fait `side_dist_x - delta_dist_x` car dans la boucle `maps != '-1'` on l'incremente
		// avant de tomber dessus donc la on recule d'un pas de rayon pour avoir la bonne valeur sure
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;

		// la hauteur de la colonne qu'on va dessiner. Plus le mur est proche, plus la colonne est haute
		line_height = (int)(HEIGHT / perp_wall_dist);

		// pixel de debut du mur centrer sur l'ecran, `clamp` a `0` si hors ecran
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
    		draw_start = 0;
		
		// pixel de fin du mur centrer sur l'ecran, `clamp` a `HEIGHT -1` si hors ecran
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
   			draw_end = HEIGHT - 1;

		// ici on effectue le dessin de la colonne pixel par pixel
		// plafond au dessus du mur, mur au milieu (rouge pour l'instant), sol en dessous du mur 
		y = 0;
		while (y < HEIGHT)
		{
			if (y < draw_start)
				ft_put_pixel(game, x, y, game->ceiling_color);
			else if (y <= draw_end)
				ft_put_pixel(game, x, y, 0xFF0000); // ici le mur est en rouge temporairement
			else
				ft_put_pixel(game, x, y, game->floor_color);
			y++;
		}
        x++;
    }
}
