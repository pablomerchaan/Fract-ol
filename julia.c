#include "fractol.h"

int calc_julia_point(complex c, int depth, t_fracdata *data)
{
  complex z;
  double tmp;
  int i;

  z.r = data->x;
  z.i = data->y;
  i = 0;
  while (i < depth)
  {
    tmp = (z.r * z.r) + (z.i * z.i);
    //printf("TMP: %d\n", tmp);
    if (tmp > 4)
      return i;
    else
    {
    	tmp = z.r * z.r - z.i * z.i + data->i;
	z.i = 2 * z.r * z.i + data->j;
	z.r = tmp;
    }
    i++;
  }
  return i;
}
