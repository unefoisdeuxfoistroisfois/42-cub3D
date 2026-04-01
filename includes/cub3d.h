#ifndef cub3D
#define cub3D

# define WIDTH 800

# define HEIGHT 800

#  include "mlx.h"
# include "../Libft/libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

// main.c

// mlx.c
void	ft_mlx(void);
void	ft_run_mlx(void *mlx_connection, void *mlx_window, t_data *data);
void	ft_init_mlx(void **mlx_connection, void **mlx_window, t_data *data);

#endif
