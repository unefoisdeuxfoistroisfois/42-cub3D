/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:33:46 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:20:09 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player(char *line, t_maps *maps)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
		{
			if (maps->player == 1)
				ft_exit_parsing(line, maps);
			maps->player = 1;
		}
		i ++;
	}
}

void	ft_grow_map(char *line, t_maps *maps)
{
	int		size;
	char	**newmap;

	size = ft_strlen_maps(maps);
	newmap = malloc(sizeof(char *) * (size + 2));
	size = 0;
	while (maps->map[size] != NULL)
	{
		newmap[size] = maps->map[size];
		size ++;
	}
	newmap[size] = ft_strdup(line);
	newmap[size + 1] = NULL;
	free(maps->map);
	maps->map = newmap;
}

void	ft_add_line(char *line, t_maps *maps)
{
	if (maps->map == NULL)
	{
		maps->map = malloc(sizeof(char *) * 2);
		maps->map[0] = ft_strdup(line);
		maps->map[1] = NULL;
	}
	else
		ft_grow_map(line, maps);
}

int	ft_check_maps(char *line, t_maps *maps)
{
	int	i;

	if (line [0] == '1' || line [0] == '0' || line[0] == ' ')
	{
		ft_player(line, maps);
		i = 0;
		while (line[i] != '\0' && line[i] != '\n')
		{
			if (line[i] != '0' && line[i] != '1' && line[i] != ' '
				&& line[i] != 'N' && line[i] != 'S'
				&& line[i] != 'W' && line[i] != 'E')
				ft_exit_parsing(line, maps);
			i ++;
		}
		ft_add_line(line, maps);
		return (1);
	}
	else
		return (0);
}
