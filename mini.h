/*----------------------------------------------------*/

#ifndef MINI_H
# define MINI_H

/*----------------------------------------------------*/

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>

/*----------------------------------------------------*/

typedef struct	s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_lenght;
	int endian;
}				t_data;

/*----------------------------------------------------*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif