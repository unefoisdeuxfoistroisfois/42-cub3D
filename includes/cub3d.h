#ifndef cub3D
#define cub3D

// Size window

# define WIDTH 2000
# define HEIGHT 2000

// KEYCODE

# define W	119
# define S	115
# define A	97
# define D	100
# define W_MAC	13		// FAUT PAS OUBLIER QU IL Y A UN PROBLEME AVEC LES FLECHES A CHANGER DANS MOVE.C AUSSI
# define A_MAC	2
# define S_MAC	1
# define D_MAC	0
# define ESC	65307
# define ESC_MAC	53
# define LEFT	65363
# define RIGHT	65361
# define LEFT_MAC	124
# define RIGHT_MAC	123

// SPEED PLAYER AND SPEED ROTATE

# define SPEED 0.05
# define ROT_SPEED 0.03

# include "mlx.h"
# include "../Libft/libft.h"
# include <stdio.h>
# include <math.h>

typedef struct s_data
{
    void    *img;
    void    *mlx;
    void    *win;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;   // AJOUT
    int     height;  // AJOUT
}   t_data;

typedef struct s_maps
{
	int	no;
  int	so;
  int	we;
  int	ea;
  int	f;
  int	c;
	int	player;
	char **map;
	// AJOUT : stockage des chemins de textures
	char    *path_no;
	char    *path_so;
	char    *path_we;
	char    *path_ea;
	// AJOUT : stockage des couleurs RGB
  int     floor[3];
  int     ceil[3];
}	t_maps;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
	double	new_pos_x;
	double	new_pos_y;
}   t_player;

// typedef struct s_raycasting
// {
// 	int     x;
// 	int		y;
// 	int		side;
// 	int		map_x;
// 	int		map_y;
// 	int 	step_x;
// 	int 	step_y;
//     double  camera_x;
// 	int		draw_end;
//     double  ray_dir_x;
//     double  ray_dir_y;
// 	int		draw_start;
// 	int		line_height;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	double	perp_wall_dist;
// }	t_ray

typedef struct s_game
{
    t_data      data; // fenetre principale 
	t_data		tex_no;
	t_data		tex_so;
	t_data		tex_we;
	t_data		tex_ea;
    t_player    player;
    t_maps      maps; // parsing
    int         floor_color; // couleur sol en 0xRRGGBB
    int         ceiling_color; // couleur plafond en 0xRRGGBB
}   t_game;

// mlx.c
void	ft_mlx(t_game *game); // au lieu de struct data direct game pour ensuite game->data ...
void	ft_run_mlx(t_game *game); // au lieu de plusieurs void params, direct la struct game
void	ft_init_mlx(t_game *game); // au lieu de plusieurs void params, direct la struct game 

// events.c
int 	ft_key(int keycode, t_game *game); // t_game *game au lieu de t_data *data

// free.c
int		ft_clean(t_game *game); // t_game *game au lieu de t_data *data 
void	ft_free_maps(t_maps *maps);

// args.c
void	ft_args(char *str, t_maps *maps); // Ajout de pointeur sur la structure maps
int		ft_is_dot_cub(char *str);
int		ft_line(char *str, t_maps *maps); // Ajout de pointeur sur la structure maps
void    ft_flags(char *line, t_maps *maps);


// texture.c
void    ft_check_texture(char *line, t_maps *maps); // Ajout de pointeur sur la structure maps 
char    *ft_path(char *line);
void    ft_valide_texture(char *path);

// colors.c
void    ft_check_colors(char *line, t_maps *maps); // Ajout de pointeur sur la structure maps
char    *ft_strcolors(char *line);
void    ft_valide_colors(char *line, int *rgb);  // Ajout de int *rgb

// maps.c
int 	ft_check_maps(char *line, t_maps *maps);
void	ft_player(char *line, t_maps *maps);

// maps2.c
int 	ft_strlen_maps(t_maps *maps);
void    ft_check_first_last_line(t_maps *maps);
void    ft_check_left_right_side(t_maps *maps);

// maps3.c
void    ft_neighbors(t_maps *maps);

//	init.c
void    ft_init_player(t_game *game);

//	init_textures.c
void	ft_init_textures(t_game *game);

//	init_colors.c
void	ft_init_colors(t_game *game);

//	render.c
void	ft_put_pixel(t_game *game, int x, int y, int color);
int		ft_render(t_game *game);

//	move.c
void	ft_rotate_player(int keycode, t_game *game);
void	ft_move_player_WS(int keycode, t_game *game);
void	ft_move_player_AD(int keycode, t_game *game);

//	raycaster.c
void    ft_raycaster(t_game *game);

#endif
