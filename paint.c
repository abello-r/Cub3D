#include "mini.h"

int	press(int keycode, t_data *data)
{
	if (keycode == 9)
	{
		data->color = COLOR1;
	}
	if (keycode == KEY_UP) //Arriba
	{
		mlx_pixel_put(data->mlx, data->win, data->x, data->y, data->color);
		data->y--;
		data->up_switch = 1;
	}
	else if (keycode == KEY_DOWN) //Abajo
	{
		mlx_pixel_put(data->mlx, data->win, data->x, data->y, 0x00ffffff);
		data->y++;
		data->down_switch = 1;
	}
	else if (keycode == KEY_RIGHT) //Derecha
	{
		mlx_pixel_put(data->mlx, data->win, data->x, data->y, 0x00ffffff);
		data->x++;
		data->right_switch = 1;
	}
	else if (keycode == KEY_LEFT) //Izquierda
	{
		mlx_pixel_put(data->mlx, data->win, data->x, data->y, 0x00ffffff);
		data->x--;
		data->left_switch = 1;
	}
	return(0);
}

int	release(int keycode, t_data *data)
{
	if (keycode == KEY_UP) //Arriba
	{
		data->up_switch = 0;
	}
	else if (keycode == KEY_DOWN) // Abajo
	{
		data->down_switch = 0;
	}
	else if (keycode == KEY_RIGHT) //Derecha
	{
		data->right_switch = 0;
	}
	else if (keycode == KEY_LEFT) //Izquierda
	{
		data->left_switch = 0;
	}
	return(0);
}

int main(void)
{
	t_data		data;
	data.x = 500;
	data.y = 40;
	data.color = COLOR;

	data.mlx	= mlx_init();
	data.win	= mlx_new_window(data.mlx, 1920, 1080, "Paint");
	data.img	= mlx_new_image(data.mlx, 1920, 1080);
	data.addr	= mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);

	mlx_hook(data.win, 02, (1L<<0), press, &data);
	mlx_hook(data.win, 03, (1L<<1), release, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}