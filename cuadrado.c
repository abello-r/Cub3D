#include "mini.h"

int close_window(int keycode, t_delete *data)
{
	char	*nro = ft_itoa(keycode);

	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode != 53 && keycode != 51)
	{
		mlx_string_put(data->mlx, data->win, 700, 700, 0x00ff0000, nro);
		printf("%s\n", nro);
	}
	else if (keycode == 51)
			mlx_clear_window(data->mlx, data->win);
	return(0);
}

int main(void)
{
	int x = 0;
	int y = 0;
	t_delete data;
	char	*str = "Este numero es el keycode de la tecla que pulses";
	t_data	img;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Cuadrado");
	img.img = mlx_new_image(data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);

	y = 270;
	while (y != 810)
	{
		my_mlx_pixel_put(&img, 480, y++, 0x00ff0000);
		if (y == 810)
		{
			y = 270;
			while(y != 810)
				my_mlx_pixel_put(&img, 1440, y++, 0x00ff0000);
		}
	}
	x = 480;
	while(x != 1440)
	{
		my_mlx_pixel_put(&img, x++, 270, 0x00ff0000);
		if(x == 1440)
		{
			x = 480;
			while(x != 1440)
				my_mlx_pixel_put(&img, x++, 810, 0x00ff0000);
		}
	}
	
	mlx_put_image_to_window(data.mlx, data.win, img.img, 0, 0);
	mlx_string_put(data.mlx, data.win, 600, 600, 0x00ff0000, str);
	mlx_key_hook(data.win, close_window, &data);
	mlx_loop(data.mlx);
}