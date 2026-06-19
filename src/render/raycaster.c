/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:04:08 by sariee            #+#    #+#             */
/*   Updated: 2026/06/15 23:44:55 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_run_dda(t_game *game, t_ray *ray)
{
		// DDA : on fait avancer le rayon case par case jusqu'a toucher un mur
		// a chaque case passer on choisit le cote le plus proche (veritcal ou horizontal)
		while (game->maps.map[ray->map_y][ray->map_x] != '1')
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;	// avance au prochain croisement vertical
				ray->map_x += ray->step_x;	// passe a la case suivante en `x`
				ray->side = 0;	// `side` = 0 -> un mur vertical a ete toucher (face `EA` ou `WE`)
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;	// avance au prochain croisement horizontal
				ray->map_y += ray->step_y;	// passe a la case suivante en `y`
				ray->side = 1;	// `side` = 1 -> un mur horizontale a ete toucher (face `NO` ou `SO`)
			}
		}
}

void	ft_init_dda(t_game *game, t_ray *ray)
{
	// c'est la distance que la rayon parcourt entre deux lignes verticales `x` et horizontales `y`
	// constante tout le long du rayon, cela sert a avancer d'une case a la fois 
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);

	// distance jusqu'au premier croisement vertical
	// le joueur est a l'interieur d'une case donc la distance est moins qu'un delta complet
	// step_x nous indique dans quelle direction le rayon avance : `1 = droite, -1 = gauche`
	if (ray->ray_dir_x > 0)
	{
		ray->side_dist_x = (ray->map_x + 1 - game->player.pos_x) * ray->delta_dist_x;
		ray->step_x = 1;
	}
	else
	{
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
		ray->step_x = -1;
	}

	// distance jusqu'au premier croisement horizontale
	// step_y nous indique dans quelle direction le rayon avance : `1 = bas, -1 = haut`
	if (ray->ray_dir_y > 0)
	{
		ray->side_dist_y = (ray->map_y + 1 - game->player.pos_y) * ray->delta_dist_y;
		ray->step_y = 1;
	}
	else
	{
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
		ray->step_y = -1;
	}
}

void	ft_calc_ray_dir(t_game *game, t_ray *ray)
{
		// `camera_x` = la position normalisee de la colonne dans l'ecran : -1 = gauche, 0 = centre, 1 = droite
        ray->camera_x = 2 * ray->x / (double)WIDTH - 1;

		// direction pour cette colonne
		// il faut combiner la direction du joueur avec le plan camera en fonction de `camera_x`
		// et plus `camera_x` est grand, plus le rayon devie vers la droite
        ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
        ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;

		// case de la grille ou se trouver le joueur et vu que pos est une varible `double`
		// `ex : 3.7` bas on le cast en int pour avoir la case `3`
		ray->map_x = (int)game->player.pos_x;
		ray->map_y = (int)game->player.pos_y;
}

// fonction principale du rendu qui tourne pour chaque frame
// pour chaque colonne x de l'ecran, lance un rayon et dessine la colonne
void    ft_raycaster(t_game *game)
{
	t_ray *ray;
	
	ray = &game->ray;
    ray->x = 0;
	// on va parcourir de `x = 0` jusqu'a la limite de `WIDTH` qui est la `largeur` de la fenetre
    while (ray->x < WIDTH)
    {
		ft_calc_ray_dir(game, ray);
		ft_init_dda(game, ray);
		ft_run_dda(game, ray);
		ft_calc_draw_bounds(ray);
		ft_select_texture(game, ray);
		ft_draw_column(game, ray);
		ray->x++;
	}
}
