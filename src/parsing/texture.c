/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:35:55 by sariee            #+#    #+#             */
/*   Updated: 2026/06/16 12:42:24 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_valide_texture(char *path)
{
	int		fd;
	int		resstrncmp;
	char	*dotxpm;

	dotxpm = ft_strrchr (path, '.');
	if (dotxpm == NULL)
	{
		printf("pas d'extention");
	    free(path);  // AJOUT free path car malloc dans strtrim
		exit(EXIT_FAILURE);
	}
	resstrncmp = ft_strncmp(dotxpm, ".xpm", 4);
	if (resstrncmp != 0)
	{
		printf("fichier n'est pas un xmp");
	    free(path);  // AJOUT free path car malloc dans strtrim
		exit(EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("fichier pas trouvé");
	    free(path);  // AJOUT free path car malloc dans strtrim
		exit(EXIT_FAILURE);
	}
	else
		printf("fichier xpm trouvé\n");
	close (fd);
}

/*  Si il trouve l'espace il avance de 1 pour trouvé le chemin et 
    ensutie on peut le comparer */
char	*ft_path(char *line)
{
	char	*path;
	char	*trimmed;

	path = ft_strchr(line, ' ');
	if (path == NULL)
	{
		printf("pas bon");
		exit(EXIT_FAILURE);
	}
	else
	{
		path = path + 1;
	}
	trimmed = ft_strtrim(path, "\n");
	return (trimmed);
}

// retourne 0 quand c'eest ok
// Je check le chemin de la jjk

/*  Je vais check si NO SO WE et EA sont bon si oui on va verifier le chemin grace a 
    ft_path qui va nous renvoyé le chemin apres les coordonnée
    et ft_valide qui va check si c'est ok avec un open*/

// SAM
// MODIFIE : ajout de t_maps *maps en parametre + stockage des paths
void	ft_check_texture(char *line, t_maps *maps)
{
	char	*path;

	if (ft_strncmp(line, "NO", 2) == 0)
	{
		path = ft_path(line);
		ft_valide_texture(path);
		maps->path_no = path; // AJOUT : stockage du path
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		path = ft_path(line);
		ft_valide_texture(path);
		maps->path_so = path; // AJOUT : stockage du path
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		path = ft_path(line);
		ft_valide_texture(path);
		maps->path_we = path; // AJOUT : stockage du path
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		path = ft_path(line);
		ft_valide_texture(path);
		maps->path_ea = path; // AJOUT : stockage du path
	}
}
