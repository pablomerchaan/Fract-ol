#include "fractol.h"

double atod(const char *str)
{
	double result;
	double sign;
	double decimalPlace;
	int i;

	i = 0;
	result = 0.0;
	sign = 1.0;
	printf("1\n");
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	{
		i++;
	}
	printf("2\n");
	if (str[i] == '-') {
		sign = -1.0;
		i++;
	}
	printf("3\n");
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	printf("4\n");
	if (str[i] == '.')
       	{
		i++;
		decimalPlace = 1.0;
	 	printf("5\n");
		while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
		{
				result = result + (str[i] - '0') * (decimalPlace /= 10.0);
				i++;
		}
	}
	result = result	* sign;
	printf("double i: %f\n", result);
	return (result);
}

char *get_fractal_name(char **argv)
{
	int i;
	int len;
	char *command;
	int cmp;

	len = ft_strlen(argv[1]) + 1;
	command = malloc(len * sizeof(char));
	i = 0;
	while (argv[1][i] != '\0')
	{
		command[i] = argv[1][i];
		i++;
	}
	command[i] = '\0';

	return command;
}

t_fracdata *construct_fracdata(double zoom, double x, double y, char ** argv)
{
	t_img *img;
	t_fracdata *data;
	void *mlx;
	char * name;

	mlx = mlx_init();
	img = (t_img*) malloc(sizeof(t_img));
	img->img = mlx_new_image(mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);

	name = get_fractal_name(argv);
	data = (t_fracdata*) malloc(sizeof(t_fracdata));
	if (!ft_strcmp(name, "julia"))
	{
	printf("i = %s, j = %s\n", argv[2], argv[3]);
		data->i = atod(argv[2]);
	printf("i = %f, j = %s\n", data->i, argv[3]);
		data->j = atod(argv[3]);
	}
	printf("after atod\n");
	data->mlx = mlx;
	data->mlx_win = mlx_new_window(mlx, 1920, 1080, "Fract-ol");
	data->img = img;
	data->zoom = zoom;
	data->x = x;
	data->y = y;
	data->name = name;
	return data;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
