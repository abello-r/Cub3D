#include "mini.h"

int main(void)
{
	int x = 0;
	int y = 0;
	void	*mlx;
	void	*mlx_win;
	char	*str = "hola";
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Cuadrado");
	img.img = mlx_new_image(mlx, 1920, 1080);
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
		my_mlx_pixel_put(&img, x++, 270, 0x0000ff00);
		if(x == 1440)
		{
			x = 480;
			while(x != 1440)
				my_mlx_pixel_put(&img, x++, 810, 0x0000ff00);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_string_put(mlx, mlx_win, 600, 600, 0x00ff0000, str);
	mlx_loop(mlx);
}