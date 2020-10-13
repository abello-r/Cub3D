#include "mini.h"


int main (void)
{	
	int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	t_global global;
	t_player player;
	int x = 0; 
	double w = 1920;

	global.data.mlx		= mlx_init();
	global.data.win		= mlx_new_window(global.data.mlx, 1920, 1080, "Cub3d");
	global.data.img		= mlx_new_image(global.data.mlx, 1920, 1080);
	global.data.addr	= mlx_get_data_addr(global.data.img, &global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);

	// Asignación de valores.
	player.posX =	22;
	player.posY =	12;
	player.dirX =	-1;
	player.dirY =	0;
	player.planeX =	0;
	player.planeY =	0.66;
	player.time =	0;
	player.old_time	= 0;



	while(x < w) // revisar las variables aquí
	{
		x++;
		player.cameraX = 2 * x / w - 1;
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
			//break; // esto va aquí mientras soluciono lo del mapa, ojito (no recuerdo por que puse esto)
		}
		else
		{
			player.sideDistY += player.deltaDistX;
			player.mapY += player.stepY;
			player.side = 1;
		}
		if (worldMap[player.mapX][player.mapY] > 0) 
			player.hit = 1;
	}

		if (player.side == 0)
		{
			player.perpWallDist = (player.mapX - player.posX + (1 - player.stepX) / 2) / player.rayDirX;
		}
		else
		{
			player.perpWallDist = (player.mapY - player.posY + (1 - player.stepY) / 2) / player.rayDirY;
		}

		global.player.line_height = (1080 / player.perpWallDist); // Calcula la altura de la linea a pintar.
		
		global.player.drawStart = -global.player.line_height / 2 + 1080 / 2;
		global.player.drawStart = (global.player.drawStart < 0) ? 0 : global.player.drawStart;
		global.player.drawEnd = global.player.line_height / 2 + 1080 / 2;
		global.player.drawEnd = (global.player.drawEnd >= 1080) ? 1080 - 1 : global.player.drawEnd;

		switch(worldMap[player.mapX][player.mapY]) // Switch no está permitido, recuerda que esto es temporal.
		{
			case 1: global.data.color = RGB_Red; break;
			case 2: global.data.color = RGB_Green; break;
			default: global.data.color = RGB_Yellow; break;
		}
		if (player.side == 1) // Esto es para darle un brillo diferente al chocar con una pared.
		{
			global.data.color = global.data.color / 2;
		}
		mlx_pixel_put(global.data.mlx, global.data.win, global.player.drawStart, global.player.drawEnd, global.data.color);

		global.player.old_time = global.player.time;
		global.player.time = 10;

		mlx_put_image_to_window(global.data.mlx, global.data.win, global.data.img, 0, 0);
		mlx_loop(global.data.mlx);
}