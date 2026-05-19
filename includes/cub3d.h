#ifndef cub3D
#define cub3D

# define WIDTH 800

# define HEIGHT 800

# include "mlx.h"
# include "../Libft/libft.h"
# include <stdio.h>

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

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
}   t_player;

typedef struct s_game
{
    t_data      data; // fenetre principale 
		t_data			tex_no;
		t_data			tex_so;
		t_data			tex_we;
		t_data			tex_ea;
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
int ft_key(int keycode, t_game *game); // t_game *game au lieu de t_data *data

// free.c
int	ft_clean(t_game *game); // t_game *game au lieu de t_data *data 

// args.c
void	ft_args(char *str, t_maps *maps); // Ajout de pointeur sur la structure maps
int	ft_is_dot_cub(char *str);
int    ft_line(char *str, t_maps *maps); // Ajout de pointeur sur la structure maps
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
int ft_check_maps(char *line, t_maps *maps);
void	ft_player(char *line, t_maps *maps);

// maps2.c
int ft_strlen_maps(t_maps *maps);
void    ft_check_first_last_line(t_maps *maps);
void    ft_check_left_right_side(t_maps *maps);

// maps3.c
void    ft_neighbors(t_maps *maps);

#endif
