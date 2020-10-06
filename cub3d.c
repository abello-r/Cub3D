#include "mini.h"

int main (void)
{
	//int		worldmap[3][6] = {{1,1,1,1,1,1},{1,0,0,0,0,1},{1,1,1,1,1,1}};
	t_global global;
	t_player player;
	
	global.data.mlx		= mlx_init();
	global.data.win		= mlx_new_window(global.data.mlx, 1920, 1080, "Cub3d");
	global.data.img		= mlx_new_image(global.data.mlx, 1920, 1080);
	global.data.addr	= mlx_get_data_addr(global.data.img, &global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);

/*	// Asignación de valores.
	player.posX =	4;
	player.posY =	2;
	player.dirX =	-1;
	player.dirY =	0;
	player.planeX =	0;
	player.planeY =	0.66;
	player.time =	0;
	player.old_time	= 0;
*/
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

		//if (worldmap[player.mapX][player.mapY] > 0) 
		//	player.hit = 1;

		if (player.side == 0)
		{
			player.perpWallDist = (player.mapX - player.posX + (1 - player.stepX) / 2) / player.rayDirX;
		}
		else
		{
			player.perpWallDist = (player.mapY - player.posY + (1 - player.stepY) / 2) / player.rayDirY;
		}

		/*int	line_height;
		int drawStart;
		int drawEnd;

		line_height = (1080 / player.perpWallDist); // Calcula la altura de la linea a pintar.
		
		drawStart = -line_height / 2 + 1080 / 2;
		drawStart = (drawStart < 0) ? 0 : drawStart;
		drawEnd = line_height / 2 + 1080 / 2;
		drawEnd = (drawEnd >= 1080) ? 1080 - 1 : drawEnd;*/






	}
	mlx_put_image_to_window(global.data.mlx, global.data.win, global.data.img, 0, 0);
	mlx_loop(global.data.mlx);

	
}