/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sariee <sariee@student.42belgium.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:36:37 by sariee            #+#    #+#             */
/*   Updated: 2026/06/18 17:16:25 by sariee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// deplacement du joueur en fonction de la touche pressee
// on calcule sa nouvelle position puis on verifie si cette nouvelle position n'est pas dans un mur `1`
// si ce n'est pas un mur on applique le changement et on deplace le joueur, sinon on ne bouge pas 
void	ft_move_player_w(t_game *game)
{
	char	**map;
	double	new_pos_x;
	double	new_pos_y;

	map = game->maps.map;
	// dir_x et dir_y forment le vecteur de direction du joueur `ex: nord = (0, -1)`
	// on multiplie la pos + dir par la vitesse de deplacement
	new_pos_x = game->player.pos_x + game->player.dir_x * SPEED;
	new_pos_y = game->player.pos_y + game->player.dir_y * SPEED;
	// on cast en `int` pour acceder a la bonne case du tableau `map[x][y]`
	// on raoute et soustrait MARGIN pour verifier les cases voisines pour eviter de coller le mur et eviter de pouvoir rentre dans un mur
	if (map[(int)new_pos_y][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)new_pos_y][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x - MARGIN)] != '1')
	{
		game->player.pos_x = new_pos_x;
		game->player.pos_y = new_pos_y;
	}
}

void	ft_move_player_s(t_game *game)
{
	char	**map;
	double	new_pos_x;
	double	new_pos_y;

	map = game->maps.map;
	// juste ici on soustrait la direction vu que c'est pour aller dans la direction opposee a celle ou regarde le joueur + veerification de MARGIN 
	new_pos_x = game->player.pos_x - game->player.dir_x * SPEED;
	new_pos_y = game->player.pos_y - game->player.dir_y * SPEED;
	if (map[(int)new_pos_y][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)new_pos_y][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x - MARGIN)] != '1')
	{
		game->player.pos_x = new_pos_x;
		game->player.pos_y = new_pos_y;
	}
}

// deplacement perpendiculaire a gauche, sans changer la direction du regard du joueur
// La perpendiculaire gauche du vecteur (dir_x, dir_y) est (-dir_y, dir_x)
// la formule est :
//   new_pos_x = pos_x + dir_y * SPEED
//   new_pos_y = pos_y - dir_x * SPEED
// + faire la meme verif de collision avec MARGIN 
void	ft_move_player_a(t_game *game)
{
	char	**map;
	double	new_pos_x;
	double	new_pos_y;

	map = game->maps.map;
	new_pos_x = game->player.pos_x + game->player.dir_y * SPEED;
	new_pos_y = game->player.pos_y - game->player.dir_x * SPEED;
	if (map[(int)new_pos_y][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)new_pos_y][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x - MARGIN)] != '1')
	{
		game->player.pos_x = new_pos_x;
		game->player.pos_y = new_pos_y;
	}
}

// deplacement perpendiculaire a droite, sans changer la direction du regard du joueur
// La perpendiculaire droite du vecteur (dir_x, dir_y) est (dir_y, -dir_x)
// l'inverse de A mais exactement la meme formule : 
//   new_pos_x = pos_x - dir_y * SPEED
//   new_pos_y = pos_y + dir_x * SPEED
// + faire la meme verif de collision avec MARGIN 
void	ft_move_player_d(t_game *game)
{
	char	**map;
	double	new_pos_x;
	double	new_pos_y;

	map = game->maps.map;
	new_pos_x = game->player.pos_x - game->player.dir_y * SPEED;
	new_pos_y = game->player.pos_y + game->player.dir_x * SPEED;
	if (map[(int)new_pos_y][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)new_pos_y][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)new_pos_x] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
		&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x - MARGIN)] != '1')
	{
		game->player.pos_x = new_pos_x;
		game->player.pos_y = new_pos_y;
	}
}

//	&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
//	&& map[(int)(new_pos_y + MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
//	&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x + MARGIN)] != '1'
//	&& map[(int)(new_pos_y - MARGIN)][(int)(new_pos_x - MARGIN)] != '1'
// ce bloc de 4 rajouter pour tout les if car je rentrais dans le mur
// quand c'etait un coin exterieur et pas interieur 
