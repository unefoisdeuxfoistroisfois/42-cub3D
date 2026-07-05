/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:30:43 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:22:11 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_maps(t_maps *maps)
{
	int	size;

	size = 0;
	while (maps->map[size] != NULL)
	{
		size ++;
	}
	return (size);
}

void	ft_check_left_right_side(t_maps *maps)
{
	int	i;
	int	sizemap;

	i = 0;
	sizemap = ft_strlen_maps(maps);
	while (i < sizemap)
	{
		ft_exit_if(maps->map[i][ft_first_non_space(maps->map[i])] != '1',
			maps);
		ft_exit_if(maps->map[i][ft_last_non_space(maps->map[i])] != '1',
			maps);
		i ++;
	}
}

void	ft_check_border_line(char *line, t_maps *maps)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		ft_exit_if(line[i] != '1' && line[i] != ' '
			&& !(line[i] >= 9 && line[i] <= 13), maps);
		i ++;
	}
}

void	ft_check_first_last_line(t_maps *maps)
{
	int	sizemap;

	sizemap = ft_strlen_maps(maps);
	ft_check_border_line(maps->map[0], maps);
	ft_check_border_line(maps->map[sizemap - 1], maps);
}
