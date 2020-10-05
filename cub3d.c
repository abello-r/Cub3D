#include "mini.h"

int main (void)
{
	int		worldmap[3][6] = {{1,1,1,1,1,1},{1,0,0,0,0,1},{1,1,1,1,1,1}};
	t_data data;
	t_player player;

	data.mlx	= mlx_init();
	data.win	= mlx_new_window(data.mlx, 1920, 1080, "Cub3d");
	data.img	= mlx_new_image(data.mlx, 1920, 1080);
	data.addr	= mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);

	player.posX = 0;

	while(player.posX < 1920)
	{
		player.posX++;
		player.cameraX = 2 * player.posX / 1920 - 1;
		player.rayDirX = player.dirX + player.planeX * player.cameraX;
		player.rayDirY = player.dirY + player.planeY * player.cameraX;
	}

	player.mapX = player.posX; // Posición en el mapa eje x.
	player.mapY = player.posY; // Posición en el mapa eje y.

	player.deltaDistX = fabs(1 / player.rayDirX); // Longitud del rayo desde un lado x a otro lado x.
	player.deltaDistY = fabs(1 / player.rayDirY); // Longitud del rayo desde un lado y a otro lado y.

	if (player.rayDirY < 0)
	{
		player.stepX = -1;
		player.sideDistX = (player.posX - player.mapX) * player.deltaDistX;
	}
	else
	{
		player.stepX = 1;
		player.sideDistX = (player.mapX + 1.0 - player.posX) * player.deltaDistX;
	}
	if (player.rayDirY < 0)
	{
		player.stepY = -1;
		player.sideDistY = (player.posY - player.mapY) * player.deltaDistY;
	}
	else
	{
		player.stepY = 1;
		player.sideDistY = (player.mapY + 1.0 - player.posY) * player.deltaDistY;
	}

	while (player.hit == 0)
	{
		if (player.sideDistX < player.sideDistY)
		{
			player.sideDistX += player.deltaDistX;
			player.mapX += player.stepX;
			player.side = 0;
		}
		else
		{
			player.sideDistY += player.deltaDistX;
			player.mapY += player.stepY;
			player.side = 1;
		}
		
		if (worldmap[player.mapX][player.mapY] > 0)
			player.hit = 1;

	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);

	
}