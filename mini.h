/*----------------------------------------------------*/

#ifndef MINI_H
# define MINI_H

/*----------------------------------------------------*/

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>

# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_LEFT			123

# define COLOR				0xffffff
# define COLOR1				0x00ff00
/*----------------------------------------------------*/

typedef struct	s_data
{
	void 	*img;
	char 	*addr;
	int 	bits_per_pixel;
	int 	line_lenght;
	int 	endian;

	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		color;
	int		up_switch;
	int		down_switch;
	int		left_switch;
	int		right_switch;

}				t_data;

/*----------------------------------------------------*/

typedef struct	s_delete
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}				t_delete;

/*----------------------------------------------------*/


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif