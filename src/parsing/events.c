/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:28:27 by sariee            #+#    #+#             */
/*   Updated: 2026/06/10 18:23:08 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// MODIFIE : t_game *game au lieu de t_data *data
int	ft_key(int keycode, t_game *game)
{
	if (keycode == 65307 || keycode == 53) // ESC
	{
		ft_clean(game); // MODIFIE : game au lieu de data
		return (0);
	}
	if (keycode == W || keycode == W_MAC || keycode == S || keycode == S_MAC)
		ft_move_player_WS(keycode, game);
	if (keycode == A || keycode == A_MAC || keycode == D || keycode == D_MAC)
		ft_move_player_AD(keycode, game);
	ft_rotate_player(keycode, game);
	return (0);
}
