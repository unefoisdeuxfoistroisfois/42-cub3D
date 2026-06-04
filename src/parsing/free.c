/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:29:39 by sariee            #+#    #+#             */
/*   Updated: 2026/06/04 16:15:24 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// MODIFIE : t_game *game au lieu de t_data *data
int	ft_clean(t_game *game)
{
	if (game->data.img) // MODIFIE : game->data.img
		mlx_destroy_image(game->data.mlx, game->data.img);
	if (game->data.win) // MODIFIE : game->data.win
		mlx_destroy_window(game->data.mlx, game->data.win);
	if (game->data.mlx) // MODIFIE : game->data.mlx
		free(game->data.mlx);
	printf("You left\n");
	exit(0);
	return (0);
}

// SAM ajout de la ft free maps pour toujours bien free la map complete avant de EXIT
void	ft_free_maps(t_maps *maps)
{
	int	i;

	if (maps->map)
	{
		i = 0;
		while (maps->map[i])
			free(maps->map[i++]);
		free(maps->map);
	}
	if (maps->path_no)
		free(maps->path_no);
	if (maps->path_so)
		free(maps->path_so);
	if (maps->path_we)
		free(maps->path_we);
	if (maps->path_ea)
		free(maps->path_ea);
}
