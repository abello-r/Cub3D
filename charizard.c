#include "mini.h"

int change(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->x, data->y);
	
	return(0);
}

int move(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
	{
		data->y--;
	}
	else if (keycode == KEY_DOWN)
	{
		data->y++;
	}
	else if (keycode == KEY_RIGHT)
	{
		data->x++;
	}
	else if (keycode == KEY_LEFT)
	{
		data->x--;
	}
	return(0);
}

int main(void)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Cub3D");

	data.img = mlx_xpm_file_to_image(data.mlx, "pika.xpm", &data.x, &data.y);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);

	mlx_hook(data.win, 02, (1L<<0), move, &data);
	mlx_loop_hook(data.mlx, change, &data);
	mlx_loop(data.mlx);

}