/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:19:39 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 21:04:26 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("ERROR\n");
		printf("USAGE : ./cub3D maps/your_map.cub\n");
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	ft_args(argv[1], &game.maps);
	ft_init_mlx(&game);
	ft_init_player(&game);
	ft_init_textures(&game);
	ft_init_colors(&game);
	ft_run_mlx(&game);
	return (0);
}
