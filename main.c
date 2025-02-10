#include "fractol.h"

int	on_mouse_hook(int key, int x, int y, t_fracdata *fracdata)
{
	if (key == 4)
	{
		fracdata->x = (x / fracdata->zoom + fracdata-> x) - (x / (fracdata->zoom / 1.1));
		fracdata->y = (y / fracdata->zoom + fracdata-> y) - (y / (fracdata->zoom / 1.1));
	}
	if (key == 5)
	{
		fracdata->x = (x / fracdata->zoom + fracdata-> x) - (x / (fracdata->zoom * 1.1));
		fracdata->y = (y / fracdata->zoom + fracdata-> y) - (y / (fracdata->zoom * 1.1));
	}
	if (key == 4 || key == 5)
		zoom(key, fracdata);
	return(0);
}

int	on_key_hook(int key, t_fracdata *data)
{
	if (key == 65307)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	static double z;
	static double x;
	static double y;
	t_fracdata *data;

	z = 500;
	x = 0;
	y = 0;
	/*if (argc != 2)*/
		/*exit(0);*/

	data = construct_fracdata(z, x, y, argv);
	paint_fixed_fractal(data, z);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	mlx_key_hook(data->mlx_win, on_key_hook, data);
	mlx_mouse_hook(data->mlx_win, *on_mouse_hook, data);
	mlx_loop(data->mlx);
}
