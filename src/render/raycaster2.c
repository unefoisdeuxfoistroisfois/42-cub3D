/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 23:41:25 by sariee            #+#    #+#             */
/*   Updated: 2026/06/19 17:20:19 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_column(t_game *game, t_ray *ray)
{
	// ici on effectue le dessin de la colonne pixel par pixel
	// plafond au dessus du mur, mur au milieu (rouge pour l'instant), sol en dessous du mur 
	ray->y = 0;
	while (ray->y < HEIGHT)
	{
		if (ray->y < ray->draw_start)
			ft_put_pixel(game, ray->x, ray->y, game->ceiling_color); // juste on dessine le plafond
		else if (ray->y <= ray->draw_end)
			ft_draw_wall_pixel(game, ray);
		else
			ft_put_pixel(game, ray->x, ray->y, game->floor_color); // juste on dessine le sol
		ray->y++;
	}
}

void	ft_draw_wall_pixel(t_game *game, t_ray *ray)
{
	double	tex_y_d;

	// position normalisee `(0 a 1)` dans la texture pour ce pixel
	// `tex_pos` avance de `tex_step` a chaque appel (donc a chaque pixel `y`)
	// et a ete initialise dans `ft_calc_draw_bounds` en tenant compte
	// du VRAI `line_height` (non clampe), pas de `draw_start` qui lui
	// peut etre coupe a `0` quand le mur depasse l'ecran
	// c'est ce qui evite le glissement de texture quand on est pres d'un mur
	tex_y_d = ray->tex_pos * ray->tex->height;
	ray->tex_y = (int)tex_y_d;
	if (ray->tex_y < 0)
		ray->tex_y = 0;
	if (ray->tex_y >= ray->tex->height)
		ray->tex_y = ray->tex->height - 1;
	// lecture du pixel `(tex_x, tex_y)` dans le buffer de la texture
	// meme formule que ft_put_pixel mais on `LIT` la couleur au lieu de l'ecrire
	ray->color = *(int *)(ray->tex->addr + (ray->tex_y * ray->tex->line_length
		+ ray->tex_x * (ray->tex->bits_per_pixel / 8)));
	// dessine le pixel lu dans la texture sur l'ecran a la position `(x, y)`
	ft_put_pixel(game, ray->x, ray->y, ray->color);
	// avance d'un `pas` dans la texture pour le prochain pixel de la colonne
	ray->tex_pos += ray->tex_step;
}

void	ft_select_texture(t_game *game, t_ray *ray)
{
	// on choisit la texture en fonction de la face du mur toucher par le rayon
	// step indique la direction du rayon : `positif = droite/bas, negatif = gauche/haut`
	// le rayon touchera toujours la face opposee a sa direction `TOUJOURS`
	if (ray->side == 0 && ray->step_x > 0)
		ray->tex = &game->tex_we; // rayon va vers l'`est`, il touche face `OUEST`
	else if (ray->side == 0 && ray->step_x < 0)
		ray->tex = &game->tex_ea; // rayon va vers l'`ouest`, il touche face `EST`
	else if (ray->side == 1 && ray->step_y > 0)
		ray->tex = &game->tex_no; // rayon va vers le `sud`, il touche face `NORD`
	else
		ray->tex = &game->tex_so;

	// rayon va vers le `nord`, il touche face `SUD`
	// wall_x = position exacte ou le rayon a touche la face du mur, entre 0 et 1
	// si side == 0 (face verticale) on utilise pos_y car le rayon se deplace en x
	// si side == 1 (face horizontale) on utilise pos_x car le rayon se deplace en y
	// perp_wall_dist * ray_dir propage la position du joueur jusqu'au mur
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;

	// on garde uniquement la partie decimale : ex 3.7 -> 0.7
	// cela donne la position relative sur la face entre 0 et 1
	ray->wall_x -= floor(ray->wall_x);

	// tex_x = colonne de la texture a afficher
	// on convertit wall_x (0 a 1) en pixel (0 a tex->width)
	ray->tex_x = (int)(ray->wall_x * ray->tex->width);
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= ray->tex->width)
		ray->tex_x = ray->tex->width - 1;
}

void	ft_calc_draw_bounds(t_ray *ray)
{
	// distance perpendiculaire entre le mur et le joueur ce qui nous evite d'avoir l'effet `fish-eye`
	// on fait `side_dist_x - delta_dist_x` car dans la boucle `maps != '-1'` on l'incremente
	// avant de tomber dessus donc la on recule d'un pas de rayon pour avoir la bonne valeur sure 
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;

	// la hauteur de la colonne qu'on va dessiner. Plus le mur est proche, plus la colonne est haute
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	
	// pixel de debut du mur centrer sur l'ecran, `clamp` a `0` si hors ecran
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	// pixel de fin du mur centrer sur l'ecran, `clamp` a `HEIGHT -1` si hors ecran
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	// `tex_step` = combien on avance dans la texture `(0 a 1)` par pixel ecran
	// plus `line_height` est grand `(mur proche)` et plus `tex_step` est petit
	// donc on `avance lentement` dans la texture ce qui donne zoom correct
	ray->tex_step = 1.0 / ray->line_height;

	// `tex_pos` = `position de depart` dans la `texture` pour le premier pixel visible
	// calcule a partir du `VRAI` centre du mur `(HEIGHT/2 - line_height/2)`
	// pas depuis `draw_start` qui peut etre `clampe` a `0` si le mur deborde de l'ecran
	// c'est cette difference qui corrige le glissement de texture
	ray->tex_pos = (ray->draw_start - HEIGHT / 2.0 + ray->line_height / 2.0)
		* ray->tex_step;
}
