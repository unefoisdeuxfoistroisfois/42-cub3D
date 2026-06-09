/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:55:35 by sariee            #+#    #+#             */
/*   Updated: 2026/06/09 15:36:14 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_colors(t_game *game)
{
	game->floor_color = game->maps.floor[0] << 16
		| game->maps.floor[1] << 8
		| game->maps.floor[2];
	game->ceiling_color = game->maps.ceil[0] << 16
		| game->maps.ceil[1] << 8
		| game->maps.ceil[2];
}
	