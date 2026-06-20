#ifndef cub3D
#define cub3D

// Size window

# define WIDTH 1200
# define HEIGHT 800

// KEYCODE

# define W	119
# define A	97
# define S	115
# define D	100
# define LEFT	65361
# define RIGHT	65363
# define ESC	65307
# define W_MAC	13
# define A_MAC	0
# define S_MAC	1
# define D_MAC	2
# define LEFT_MAC	123
# define RIGHT_MAC	124
# define ESC_MAC	53

// Brad : mlx_mouse_move n'a pas la meme signature sur Mac et Linux
# ifdef __APPLE__
#  define MLX_MOUSE_MOVE(mlx, win, x, y) mlx_mouse_move(win, x, y)
# else
#  define MLX_MOUSE_MOVE(mlx, win, x, y) mlx_mouse_move(mlx, win, x, y)
# endif

// SPEED PLAYER AND SPEED ROTATE

# define SPEED 0.0225
# define ROT_SPEED 0.0225
# define MOUSE_SPEED 0.0005

// MARGIN == marge avant d'etre contre le mur pour ne pas etre dedans

# define MARGIN 0.15

// Minimap

# define MINI_SIZE  5   // taille d'une case en pixels
# define MINI_RANGE 10  // nombre de cases visibles autour du joueur
# define MINI_OFF_X 10  // marge depuis le bord droit
# define MINI_OFF_Y 10  // marge depuis le bord haut

# include "mlx.h"
# include "../Libsriee/Include/libsriee.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;   // AJOUT
	int		height;  // AJOUT
}   t_data;

typedef struct s_maps
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		player;
	char	**map;
	// AJOUT : stockage des chemins de textures
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	// AJOUT : stockage des couleurs RGB
	int		floor[3];
	int		ceil[3];
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

typedef struct s_raycasting
{
	int     x;
	int		y;
	int		side;
	int		map_x;
	int		map_y;
	int 	step_x;
	int 	step_y;
    double  camera_x;
	int		draw_end;
    double  ray_dir_x;
    double  ray_dir_y;
	int		draw_start;
	int		line_height;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	// variable rien que pour afficher les textures en dessous de ce commentaire
	t_data	*tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		color;
	double	tex_step;
	double	tex_pos;
}	t_ray;

typedef struct s_minimap
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	color;
}	t_minimap;

typedef struct s_game
{
    t_data		data; // fenetre principale 
	t_data		tex_no;
	t_data		tex_so;
	t_data		tex_we;
	t_data		tex_ea;
    t_player	player;
    t_maps		maps; // parsing
    int			floor_color; // couleur sol en 0xRRGGBB
    int			ceiling_color; // couleur plafond en 0xRRGGBB
    int			keys[6]; // 0=W 1=S 2=A 3=D 4=LEFT 5=RIGHT
	t_ray		ray;
	t_minimap	minimap;
}   t_game;

// mlx.c
void	ft_mlx(t_game *game); // au lieu de struct data direct game pour ensuite game->data ...
void	ft_run_mlx(t_game *game); // au lieu de plusieurs void params, direct la struct game
void	ft_init_mlx(t_game *game); // au lieu de plusieurs void params, direct la struct game 

// events.c
int 	ft_key_press(int keycode, t_game *game); // t_game *game au lieu de t_data *data
int 	ft_key_release(int keycode, t_game *game); // t_game *game au lieu de t_data *data
int		ft_mouse(int x, int y, t_game *game);

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
void	ft_move_player_w(t_game *game);
void	ft_move_player_s(t_game *game);
void	ft_move_player_a(t_game *game);
void	ft_move_player_d(t_game *game);

// rotate.c
void   	ft_rotate_angle(double rot, t_game *game);
void	ft_rotate_player(int keycode, t_game *game);

//	raycaster.c
void	ft_draw_column(t_game *game, t_ray *ray);
void	ft_draw_wall_pixel(t_game *game, t_ray *ray);
void	ft_select_texture(t_game *game, t_ray *ray);
void	ft_calc_draw_bounds(t_ray *ray);
void	ft_run_dda(t_game *game, t_ray *ray);
void	ft_init_dda(t_game *game, t_ray *ray);
void	ft_calc_ray_dir(t_game *game, t_ray *ray);
void    ft_raycaster(t_game *game);

// minimap.c
void	ft_draw_minimap(t_game *game);

#endif
