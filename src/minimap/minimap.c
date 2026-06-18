/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:47:51 by sariee            #+#    #+#             */
/*   Updated: 2026/06/18 15:56:35 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_mini_square(t_game *game, int screen_x, int screen_y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MINI_SIZE)
	{
		dx = 0;
		while (dx < MINI_SIZE)
		{
			// protection : ne pas ecrire hors de l'ecran
			if (screen_x + dx >= 0 && screen_x + dx < WIDTH
				&& screen_y + dy >= 0 && screen_y + dy < HEIGHT)
				ft_put_pixel(game, screen_x + dx, screen_y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	ft_draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;

	i = -MINI_RANGE;
	while (i <= MINI_RANGE)
	{
		j = -MINI_RANGE;
		while (j <= MINI_RANGE)
		{
			map_x = (int)game->player.pos_x + j;
			map_y = (int)game->player.pos_y + i;
			// position sur l'ecran en haut a gauche pour l'instant
			screen_x = (j + MINI_RANGE) * MINI_SIZE + MINI_OFF_X;
			screen_y = (i + MINI_RANGE) * MINI_SIZE + MINI_OFF_Y;
			// verifications dans l'ordre pour eviter le segfault
			// on verifie d'abord les limites avant d'acceder au tableau
			if (map_x < 0 || map_y < 0)
				color = 0x000000; // hors map (coordonnees negatives) -> noir
			else if (map_y >= ft_strlen_maps(&game->maps))
				color = 0x000000; // map_y depasse le nombre de lignes de la map -> noir
			else if (game->maps.map[map_y] == NULL)
				color = 0x000000; // ligne inexistante -> noir
			else if (map_x >= (int)ft_strlen(game->maps.map[map_y]))
				color = 0x000000; // map_x depasse la longueur de la ligne -> noir
			else if (game->maps.map[map_y][map_x] == '1')
				color = 0xAAAAAA; // mur -> gris clair
			else
				color = 0x333333; // case vide -> gris fonce
			// le joueur est toujours au centre de la minimap
			// on ecrase la couleur precedente par du rouge
			if (j == 0 && i == 0)
				color = 0xFF0000; // position du joueur -> rouge
			ft_draw_mini_square(game, screen_x, screen_y, color);
			j++;
		}
		i++;
	}
}

