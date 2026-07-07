/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:29:39 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:59:09 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_clean(t_game *game)
{
	if (game->tex_no.img)
		mlx_destroy_image(game->data.mlx, game->tex_no.img);
	if (game->tex_so.img)
		mlx_destroy_image(game->data.mlx, game->tex_so.img);
	if (game->tex_we.img)
		mlx_destroy_image(game->data.mlx, game->tex_we.img);
	if (game->tex_ea.img)
		mlx_destroy_image(game->data.mlx, game->tex_ea.img);
	if (game->data.img)
		mlx_destroy_image(game->data.mlx, game->data.img);
	if (game->data.win)
		mlx_destroy_window(game->data.mlx, game->data.win);
	ft_free_maps(&game->maps);
	if (game->data.mlx)
	{
		free(game->data.mlx);
	}
	printf("YOU LEFT\n");
	exit(0);
	return (0);
}

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

void	ft_exit_if(int cond, t_maps *maps)
{
	if (cond)
	{
		ft_free_maps(maps);
		exit(EXIT_FAILURE);
	}
}

void	ft_exit_parsing(char *line, t_maps *maps)
{
	if (line)
		free(line);
	ft_free_maps(maps);
	exit(EXIT_FAILURE);
}

void	ft_check_complete(t_maps *maps)
{
	if (maps->no == 0 || maps->so == 0 || maps->we == 0 || maps->ea == 0
		|| maps->f == 0 || maps->c == 0)
		ft_exit_if(1, maps);
	if (maps->player == 0)
		ft_exit_if(1, maps);
}
