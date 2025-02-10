#ifndef FRACTOL_H
# define FRACTOL_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct complex {
  double r;
  double i;
} complex;

typedef struct fracdata {
	void	*mlx;
	void	*mlx_win;
	t_img	*img;
  double zoom;
  double x;
  double y;
	char *name;
  double i;
  double j;
} t_fracdata;

int	ft_strlen(const char *s);
int calc_julia_point(complex c, int depth, t_fracdata *data);
int calc_mandelbrot_point(complex c, int depth);
void paint_fixed_fractal(t_fracdata *data, double z);
void zoom(int key, t_fracdata *fracdata);
t_fracdata *construct_fracdata(double zoom, double x, double y, char ** argv);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
int	ft_strcmp(char *s1, char *s2);

#endif
