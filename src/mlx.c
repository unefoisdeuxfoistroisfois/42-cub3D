#include "cub3d.h"

void	ft_init_mlx(void **mlx_connection, void **mlx_window, t_data *data)
{
	// La connexion avec le système graphique, qui retourne un pointeur *mlx
	*mlx_connection = mlx_init();

	// Crée une fenêtre de la taille donnée avec un titre.
	*mlx_window = mlx_new_window(*mlx_connection, WIDTH, HEIGHT, "cub3D");

	//	Crée une image en mémoire (le buffer où on vas dessiner).
	data->img = mlx_new_image(*mlx_connection, WIDTH, HEIGHT);

	// Récupère l'adresse du buffer de l'image pour pouvoir écrire dedans pixel par pixel
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	ft_run_mlx(void *mlx_connection, void *mlx_window, t_data *data)
{
	//envoie l'image du buffer vers la fenêtre pour l'afficher.
	mlx_put_image_to_window(mlx_connection, mlx_window, data->img, 0, 0);

	// Lance la boucle infini
	mlx_loop(mlx_connection);
}

void	ft_mlx(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	t_data	data;

	ft_init_mlx(&mlx_connection, &mlx_window, &data);
	ft_run_mlx(mlx_connection, mlx_window, &data);
}