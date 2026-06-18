/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:55:35 by sariee            #+#    #+#             */
/*   Updated: 2026/06/18 21:56:29 by sariee           ###   ########.fr       */
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
// Conversion des couleurs RGB stockees dans maps.floor[3] et maps.ceil[3]
// en un seul entier 0xRRGGBB utilisable par MLX pour dessiner les pixels.
//
// Un int couleur MLX est organise en 4 octets : 0x00 RR GG BB
// Chaque composante RGB occupe 8 bits :
//   R << 16 -> place R dans les bits 16-23 (octet rouge)
//   G << 8  -> place G dans les bits 8-15  (octet vert)
//   B       -> reste dans les bits 0-7     (octet bleu)
//   |       -> combine les trois avec un OU binaire en un seul int
//
// Exemple avec F 220,100,0 :
//   220 << 16 = 0x00DC0000
//   100 << 8  = 0x00006400
//   0         = 0x00000000
//   resultat  = 0x00DC6400  -> orange