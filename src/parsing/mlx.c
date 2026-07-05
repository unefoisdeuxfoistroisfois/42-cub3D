/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:34:43 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:25:16 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mlx(t_game *game)
{
	game->data.mlx = mlx_init();
	game->data.win = mlx_new_window(game->data.mlx, WIDTH, HEIGHT, "cub3D");
	game->data.img = mlx_new_image(game->data.mlx, WIDTH, HEIGHT);
	game->data.addr = mlx_get_data_addr(game->data.img,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
}

void	ft_run_mlx(t_game *game)
{
	ft_raycaster(game);
	mlx_hook(game->data.win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->data.win, 3, 1L << 1, ft_key_release, game);
	mlx_hook(game->data.win, 6, 1L << 6, ft_mouse, game);
	mlx_hook(game->data.win, 17, 0, ft_clean, game);
	mlx_loop_hook(game->data.mlx, ft_render, game);
	mlx_put_image_to_window(game->data.mlx, game->data.win,
		game->data.img, 0, 0);
	mlx_loop(game->data.mlx);
}

void	ft_mlx(t_game *game)
{
	ft_init_mlx(game);
	ft_run_mlx(game);
}
