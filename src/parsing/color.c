/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:21:48 by sariee            #+#    #+#             */
/*   Updated: 2026/06/18 17:44:37 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// SAM Ajout de int *rgb en parametre pour stocker les valeurs
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
			printf("Les données des couleurs sont trop grand ou trop petit");
			ft_free_split(ressplit); // SAM ajout de ma fonction ft free split car tu exit sans free lors que tu malloc avec split
			exit(EXIT_FAILURE);
		}
		rgb[i] = resatoi; // AJOUT : stockage de la valeur RGB
		i++;
	}
	if (i != 3)
	{
		printf("Erreur il faut au moin 3 valeur");
		ft_free_split(ressplit); // SAM ajout de ma fonction ft free split car tu exit sans free lors que tu malloc avec split
		exit(EXIT_FAILURE);
	}
	ft_free_split(ressplit); // SAM ajout cas normal tout est ok juste free ressplit.
}

char	*ft_strcolors(char *line)
{
	char	*res;
	char	*trimmed;

	res = ft_strchr(line, ' ');
	if (res == NULL)
	{
		printf("pas bon");
		exit(EXIT_FAILURE);
	}
	else
	{
		res = res + 1;
	}
	trimmed = ft_strtrim(res, "\n");
	return (trimmed);
}

// SAM Ajout de t_maps *maps en parametre + stockage des couleurs
void	ft_check_colors(char *line, t_maps *maps)
{
	char	*resstrcolors;

	if (ft_strncmp(line, "F ", 2) == 0) // on met F puis espace pour etre sur de trouver la couleur si les textures ne fonctionne pas 
	{
		resstrcolors = ft_strcolors(line);
		ft_valide_colors(resstrcolors, maps->floor); // AJOUT : passe maps->floor
		free(resstrcolors);
	}
	if (ft_strncmp(line, "C ", 2) == 0) // on met C puis espace pour etre sur de trouver la couleur si les textures ne fonctionne pas 
	{
		resstrcolors = ft_strcolors(line);
		ft_valide_colors(resstrcolors, maps->ceil); // AJOUT : passe maps->ceil
		free(resstrcolors);
	}
}

/*
    1. Verifier F et C dans notre chaine
    2. utilisé split pour séparé ','
    3. atoi pour avoir des int.
    4. verifier que c'est entre 0 et 255.
*/
