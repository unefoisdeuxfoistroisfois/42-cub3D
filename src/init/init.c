/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:47:57 by sariee            #+#    #+#             */
/*   Updated: 2026/06/19 00:11:25 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initialisation du champ de vision du joueur. 
static void	ft_init_fov(t_game *game, int j)
{
	if (j == 'N')
	{
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	if (j == 'S')
	{
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	if (j == 'E')
	{
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	if (j == 'W')
	{
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

// Initialisation de la direction du joueur. 
static void	ft_init_direction(t_game *game, int j)
{
	if (j == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	if (j == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	if (j == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	if (j == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}

// initialisation de la positon, direction,
// plan de la camera (FOV) du joueur. 
void	ft_init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->maps.map[i] != NULL)
	{
		j = 0;
		while (game->maps.map[i][j] != '\0')
		{
			if (game->maps.map[i][j] == 'N' || game->maps.map[i][j] == 'S'
				|| game->maps.map[i][j] == 'E' || game->maps.map[i][j] == 'W')
			{
				game->player.pos_x = j + 0.5; // position initial du jouer dans la map pos x + 0.5 sinon il peut etre caller dans un mur c'est pour bien centrer le joueur
				game->player.pos_y = i + 0.5; // position initial du jouer dans la map pos y + 0.5 sinon il peut etre caller dans un mur c'est pour bien centrer le joueur
				ft_init_direction(game, game->maps.map[i][j]);
				ft_init_fov(game, game->maps.map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
