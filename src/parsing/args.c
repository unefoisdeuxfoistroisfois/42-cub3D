/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 02:26:50 by britela-          #+#    #+#             */
/*   Updated: 2026/07/05 20:31:52 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_flags(char *line, t_maps *maps)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		maps->no = 1;
	if (ft_strncmp(line, "SO ", 3) == 0)
		maps->so = 1;
	if (ft_strncmp(line, "WE ", 3) == 0)
		maps->we = 1;
	if (ft_strncmp(line, "EA ", 3) == 0)
		maps->ea = 1;
	if (ft_strncmp(line, "F ", 2) == 0)
		maps->f = 1;
	if (ft_strncmp(line, "C ", 2) == 0)
		maps->c = 1;
}

int	ft_read_lines(int fd, t_maps *maps)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
		{
			ft_flags(line, maps);
			ft_check_texture(line, maps);
			ft_check_colors(line, maps);
			ft_check_maps(line, maps);
			free(line);
		}
		else
			free (line);
		line = get_next_line(fd);
	}
	return (0);
}

int	ft_line(char *str, t_maps *maps)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	ft_read_lines(fd, maps);
	close (fd);
	ft_check_first_last_line(maps);
	ft_check_left_right_side(maps);
	ft_neighbors(maps);
	ft_check_complete(maps);
	return (0);
}

int	ft_is_dot_cub(char *str)
{
	char	*dotcub;
	int		resstrcmp;

	dotcub = ft_strchr (str, '.');
	if (dotcub == NULL)
	{
		return (0);
	}
	resstrcmp = ft_strncmp(dotcub, ".cub", 4);
	if (resstrcmp != 0)
	{
		return (0);
	}
	return (1);
}

void	ft_args(char *str, t_maps *maps)
{
	int	res;

	res = ft_is_dot_cub(str);
	if (res == 0)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_line(str, maps);
	}
}
