/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:35:55 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 20:28:03 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_valide_texture(char *path, char *line, t_maps *maps)
{
	int		fd;
	int		resstrncmp;
	char	*dotxpm;

	dotxpm = ft_strrchr (path, '.');
	if (dotxpm == NULL)
	{
		free(path);
		ft_exit_parsing(line, maps);
	}
	resstrncmp = ft_strncmp(dotxpm, ".xpm", 4);
	if (resstrncmp != 0)
	{
		free(path);
		ft_exit_parsing(line, maps);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_exit_parsing(line, maps);
	}
	else
		close (fd);
}

char	*ft_path(char *line, t_maps *maps)
{
	char	*path;
	char	*trimmed;

	path = ft_strchr(line, ' ');
	if (path == NULL)
	{
		ft_exit_parsing(line, maps);
	}
	else
	{
		path = path + 1;
	}
	trimmed = ft_strtrim(path, "\n");
	return (trimmed);
}

void	ft_store_texture(char *line, char *tag, char **dest, t_maps *maps)
{
	char	*path;

	if (ft_strncmp(line, tag, 2) == 0)
	{
		path = ft_path(line, maps);
		ft_valide_texture(path, line, maps);
		*dest = path;
	}
}

void	ft_check_texture(char *line, t_maps *maps)
{
	ft_store_texture(line, "NO", &maps->path_no, maps);
	ft_store_texture(line, "SO", &maps->path_so, maps);
	ft_store_texture(line, "WE", &maps->path_we, maps);
	ft_store_texture(line, "EA", &maps->path_ea, maps);
}
