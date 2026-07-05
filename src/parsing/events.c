/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:28:27 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:45:17 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC || keycode == ESC_MAC)
		ft_clean(game);
	if (keycode == W || keycode == W_MAC)
		game->keys[0] = 1;
	if (keycode == S || keycode == S_MAC)
		game->keys[1] = 1;
	if (keycode == A || keycode == A_MAC)
		game->keys[2] = 1;
	if (keycode == D || keycode == D_MAC)
		game->keys[3] = 1;
	if (keycode == LEFT || keycode == LEFT_MAC)
		game->keys[4] = 1;
	if (keycode == RIGHT || keycode == RIGHT_MAC)
		game->keys[5] = 1;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == W || keycode == W_MAC)
		game->keys[0] = 0;
	if (keycode == S || keycode == S_MAC)
		game->keys[1] = 0;
	if (keycode == A || keycode == A_MAC)
		game->keys[2] = 0;
	if (keycode == D || keycode == D_MAC)
		game->keys[3] = 0;
	if (keycode == LEFT || keycode == LEFT_MAC)
		game->keys[4] = 0;
	if (keycode == RIGHT || keycode == RIGHT_MAC)
		game->keys[5] = 0;
	return (0);
}

int	ft_mouse(int x, int y, t_game *game)
{
	int	delta;

	(void)y;
	delta = x - WIDTH / 2;
	if (delta == 0)
		return (0);
	ft_rotate_angle(delta * MOUSE_SPEED, game);
	MLX_MOUSE_MOVE(game->data.mlx, game->data.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
