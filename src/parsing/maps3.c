/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:32:35 by sariee            #+#    #+#             */
/*   Updated: 2026/07/09 15:43:06 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_first_non_space(char *str)
{
	int	j;

	j = 0;
	while ((str[j] >= 9 && str[j] <= 13) || str[j] == ' ')
		j ++;
	return (j);
}

int	ft_last_non_space(char *str)
{
	int	j;

	j = ft_strlen(str) - 1;
	while ((str[j] >= 9 && str[j] <= 13) || str[j] == ' ')
		j --;
	return (j);
}

char	ft_char_at(char *row, int j)
{
	if (j < 0 || j >= (int)ft_strlen(row))
		return (' ');
	return (row[j]);
}

void	ft_neighbors(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps->map[i] != NULL)
	{
		j = 0;
		while (maps->map[i][j] != '\0' && maps->map[i][j] != '\n')
		{
			if (maps->map[i][j] == '0')
			{
				ft_exit_if(i > 0
					&& ft_char_at(maps->map[i - 1], j) == ' ', maps);
				ft_exit_if(maps->map[i + 1] != NULL
					&& ft_char_at(maps->map[i + 1], j) == ' ', maps);
				ft_exit_if(j > 0 && maps->map[i][j - 1] == ' ', maps);
				ft_exit_if(maps->map[i][j + 1] != '\0'
					&& maps->map[i][j + 1] == ' ', maps);
			}
			j ++;
		}
		i ++;
	}
}
