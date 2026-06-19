/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:28:27 by sariee            #+#    #+#             */
/*   Updated: 2026/06/19 12:36:02 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// MODIFIE : t_game *game au lieu de t_data *data
// fonction boolean pour savoir quand la touche est entrain d'etre presser 
// touche pressee -> met le flag a 1
int ft_key_press(int keycode, t_game *game)
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

// fonction boolean pour savoir quand la touche a ete relachee 
// touche relachee -> remet le flag a 0
int ft_key_release(int keycode, t_game *game)
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

// rotation de la camera a la place des fleches avec la souris
// delta = distance horizontale entre la souris et le centre de l'ecran
// Si delta > 0 la souris est a droite du centre -> rotation vers la droite
// Si delta < 0 la souris est a gauche du centre -> rotation vers la gauche
// delta est multiplie par MOUSE_SPEED pour convertir un nombre de pixels
// en un petit angle de rotation exploitable par ft_rotate_angle
// On recentre ensuite la souris avec mlx_mouse_move pour qu'elle ne
// sorte jamais de la fenetre et qu'on puisse tourner indefiniment
int	ft_mouse(int x, int y, t_game *game)
{
	int delta;
	
	(void)y;
	delta = x - WIDTH / 2;
	if (delta == 0)
		return (0);
	ft_rotate_angle(delta * MOUSE_SPEED, game);
	mlx_mouse_move(game->data.mlx, game->data.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
