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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


// mlx.c
void	ft_mlx(void);
void	ft_run_mlx(void *mlx_connection, void *mlx_window, t_data *data);
void	ft_init_mlx(void **mlx_connection, void **mlx_window, t_data *data);

// events.c
int ft_key(int keycode, t_data *data);

// free.c
int	ft_clean(t_data *data);

// args.c
void    ft_args(char *str);
int    ft_is_dot_cub(char *str);

// texture.c
void    ft_check_texture(char *line);
char    *ft_path(char *line);
void    ft_valide_texture(char *path);

// colors.c
void    ft_check_colors(char *line);
char    *ft_strcolors(char *line);
void    ft_valide_colors(char *line);

#endif