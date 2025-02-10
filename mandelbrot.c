#include "fractol.h"

int calc_mandelbrot_point(complex c, int depth)
{
	complex z;
	double tmp;
	int i;

	z = (complex) {
		.r = 0,
		.i = 0,
	};
	i = 0;
	while (i < depth)
	{
		tmp = (z.r * z.r) + (z.i * z.i);
		if (tmp > 4) {
			return i;
		}
		else
		{
			tmp = z.r * z.r - z.i * z.i + c.r;
			z.i = 2 * z.r * z.i + c.i;
			z.r = tmp;
		}
		i++;
	}
	return i;
}

int	get_color(double line, double column, t_fracdata *data, double z)
{
	complex *point;
	int in_set;
	int color;
	double real;
	double imag;

	real = (line / z) + data->x;
	imag = (column / z) + data->y;
	point = &(complex) {
		.r = real,
		.i = imag,
	};

	if(!ft_strcmp(data->name, "mandelbrot"))
		in_set = calc_mandelbrot_point(*point, 1000);
	if(!ft_strcmp(data->name, "julia"))
		in_set = calc_julia_point(*point, 1000, data);
	if (in_set == 1000)
		color = create_trgb(0, 0, 255, 0);
	else if (in_set < 20)
		color = create_trgb(0, 255, 0, 0);
	else if (in_set >= 30)
		color = create_trgb(0, 185, 40, 30);
	else if (in_set <= 40)
		color = create_trgb(0, 205, 20, 30);
	else if (in_set <= 50)
		color = create_trgb(0, 165, 60, 30);
	else if (in_set <= 60)
		color = create_trgb(0, 155, 70, 30);
	else if (in_set <= 80)
		color = create_trgb(0, 100, 100, 55);
	else if (in_set <= 100)
		color = create_trgb(0, 95, 120, 40);
	else if (in_set <= 120)
		color = create_trgb(0, 85, 170, 0);
	else if (in_set > 120)
		color = create_trgb(0, 50, 205, 0);
	return (color);
}

void paint_fixed_fractal(t_fracdata *data, double z)
{
	int line;
	int column;
	int color;

	line = 0;
	while (line < 1920)
	{
		column = 0;
		while (column < 1080) {
			color = get_color(line, column, data, z);
			my_mlx_pixel_put(data->img, line, column, color);
			column++;
		}
		line++;
	}
}

void zoom(int key, t_fracdata *fracdata)
{
	double z;
	//mlx_clear_window(&fracdata->mlx, &fracdata->mlx_win);
	mlx_destroy_image(fracdata->mlx, fracdata->img->img);
	fracdata->img->img = mlx_new_image(fracdata->mlx, 1920, 1080);
	fracdata->img->addr = mlx_get_data_addr(fracdata->img->img, &fracdata->img->bits_per_pixel, &fracdata->img->line_length,
								&fracdata->img->endian);
	if (key == 4)
		z = fracdata->zoom / 1.1;
	else if (key == 5)
		z = fracdata->zoom * 1.1;
	paint_fixed_fractal(fracdata, z);
	fracdata->zoom = z;
	mlx_put_image_to_window(fracdata->mlx, fracdata->mlx_win, fracdata->img->img, 0, 0);
}
