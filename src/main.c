#include "cub3d.h"

int	main(void)
{
	t_cub	cub;

	ft_init_mlx(&cub);
	mlx_loop(cub.mlx);
	return (0);
}