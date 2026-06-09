/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:04:08 by sariee            #+#    #+#             */
/*   Updated: 2026/06/09 18:45:14 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// fonction qui tourne pour chaque frame 
void    ft_raycaster(t_game *game)
{
    int     x;
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
	// on va parcourir de x = 0 jusqu'a la limite de WIDTH.
    while (x < WIDTH)
    {
        camera_x = 2 * x / (double)WIDTH - 1;	// camera_x = la position de la colonne dans l'ecran et au plus camera x est grand au plus le rayon devie vers la droite.
        ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;	// la direction du rayon pour cette colonne.
        ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;	// la direction du rayon pour cette colonne.
		map_x = (int)game->player.pos_x;
		map_y = (int)game->player.pos_y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
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
		while (game->maps.map[map_y][map_x] != '1')
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;	// side 0 un mur vertical a ete toucher
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;	// side = 1 un mur horizontale a ete toucher 
			}
		}
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;	// distance perpendiculaire entre le mur et le joueur.
		else
			perp_wall_dist = side_dist_y - delta_dist_y;	// distance perpendiculaire entre le mur et le joueur.
		line_height = (int)(HEIGHT / perp_wall_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
    		draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
   			draw_end = HEIGHT - 1;
		// pas terminer encore !!!
        x++;
    }
}
