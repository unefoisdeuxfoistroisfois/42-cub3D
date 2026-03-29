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

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_cub;

void	ft_init_mlx(t_cub *cub);

#endif
