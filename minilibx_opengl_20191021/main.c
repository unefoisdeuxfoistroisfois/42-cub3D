#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH  800
#define HEIGHT 600

int	key_hook(int keycode, void *param)
{
	(void)param;
	printf("keycode = %d\n", keycode);

	if (keycode == 53) // ESC sur Mac
		exit(0);

	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		return (1);

	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Keycode Test");
	if (!win)
		return (1);

	mlx_key_hook(win, key_hook, NULL);
	mlx_loop(mlx);
	return (0);
}
