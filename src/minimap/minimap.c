/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 12:47:51 by sariee            #+#    #+#             */
/*   Updated: 2026/06/18 20:15:09 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_mini_square(t_game *game, int screen_x,
		int screen_y, int color)
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

static void	ft_check_minimap_segfault(t_game *game, t_minimap *mini)
{
	// verifications dans l'ordre pour eviter le segfault
	// on verifie d'abord les limites avant d'acceder au tableau
	if (mini->map_x < 0 || mini->map_y < 0)
		mini->color = 0x000000; // hors map (coordonnees negatives) -> noir
	else if (mini->map_y >= ft_strlen_maps(&game->maps))
		mini->color = 0x000000; // map_y depasse le nombre de lignes de la map -> noir
	else if (game->maps.map[mini->map_y] == NULL)
		mini->color = 0x000000; // ligne inexistante -> noir
	else if (mini->map_x >= (int)ft_strlen(game->maps.map[mini->map_y]))
		mini->color = 0x000000; // map_x depasse la longueur de la ligne -> noir
	else if (game->maps.map[mini->map_y][mini->map_x] == '1')
		mini->color = 0xAAAAAA; // mur -> gris clair
	else
		mini->color = 0x333333; // case vide -> gris fonce
}

void	ft_draw_minimap(t_game *game)
{
	t_minimap	*mini;

	mini = &game->minimap;
	mini->i = -MINI_RANGE;
	while (mini->i <= MINI_RANGE)
	{
		mini->j = -MINI_RANGE;
		while (mini->j <= MINI_RANGE)
		{
			mini->map_x = (int)game->player.pos_x + mini->j;
			mini->map_y = (int)game->player.pos_y + mini->i;
			// position de la case sur l'ecran — minimap en haut a droite
			// WIDTH - taille_totale_minimap - marge + position_relative_dans_minimap
			mini->screen_x = WIDTH - (MINI_RANGE * 2 + 1) * MINI_SIZE
				- MINI_OFF_X + (mini->j + MINI_RANGE) * MINI_SIZE;
			// screen_y : depuis le haut de l'ecran avec marge
			mini->screen_y = (mini->i + MINI_RANGE) * MINI_SIZE + MINI_OFF_Y;
			ft_check_minimap_segfault(game, mini);
			// le joueur est toujours au centre de la minimap
			// on ecrase la couleur precedente par du rouge
			if (mini->j == 0 && mini->i == 0)
				mini->color = 0xFF0000; // position du joueur -> rouge
			ft_draw_mini_square(game, mini->screen_x, mini->screen_y, mini->color);
			mini->j++;
		}
		mini->i++;
	}
}
