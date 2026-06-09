/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:44:15 by sariee            #+#    #+#             */
/*   Updated: 2026/06/09 16:26:05 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_game *game, int x, int y, int color)
{
	char    *dst;

	dst = game->data.addr + (y * game->data.line_length + x * (game->data.bits_per_pixel / 8));
	// on cast dst `(unsigned int *)dst` pour qu'il traite dst comme un pointeur vers 4 bytes au lieu de 1 byte
	// ensuite on rajoute le pointeur `*(unsignmed int*)dstdevant la paranthese pour qu'il ecrit les 4 bytes d'un coup
	*(unsigned int *)dst = color;
}