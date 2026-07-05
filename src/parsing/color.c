/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:21:48 by sariee            #+#    #+#             */
/*   Updated: 2026/07/05 21:45:10 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_valide_colors(char *line, int *rgb)
{
	char	**ressplit;
	int		resatoi;
	int		i;

	ressplit = ft_split(line, ',');
	i = 0;
	while (ressplit[i] != NULL)
	{
		resatoi = ft_atoi(ressplit[i]);
		if (resatoi < 0 || resatoi > 255)
		{
			ft_free_split(ressplit);
			exit(EXIT_FAILURE);
		}
		rgb[i] = resatoi;
		i++;
	}
	if (i != 3)
	{
		ft_free_split(ressplit);
		exit(EXIT_FAILURE);
	}
	ft_free_split(ressplit);
}

char	*ft_strcolors(char *line)
{
	char	*res;
	char	*trimmed;

	res = ft_strchr(line, ' ');
	if (res == NULL)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		res = res + 1;
	}
	trimmed = ft_strtrim(res, "\n");
	return (trimmed);
}

void	ft_check_colors(char *line, t_maps *maps)
{
	char	*resstrcolors;

	if (ft_strncmp(line, "F ", 2) == 0)
	{
		resstrcolors = ft_strcolors(line);
		ft_valide_colors(resstrcolors, maps->floor);
		free(resstrcolors);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		resstrcolors = ft_strcolors(line);
		ft_valide_colors(resstrcolors, maps->ceil);
		free(resstrcolors);
	}
}
