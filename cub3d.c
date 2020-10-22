#include "mini.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
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

int raycasting(t_global *global)
{
	int	w = 1920;
	int x = 0; 
	int y = 0;

	while(x < w) // revisar las variables aquí
	{
		global->player.cameraX = 2 * x / (double)w - 1;
		global->player.rayDirX = global->player.dirX + global->player.planeX * global->player.cameraX;
		global->player.rayDirY = global->player.dirY + global->player.planeY * global->player.cameraX;

		global->player.mapX = (int)global->player.posX; // Posición en el mapa eje x.
		global->player.mapY = (int)global->player.posY; // Posición en el mapa eje y.

		global->player.deltaDistX = fabs(1 / global->player.rayDirX); // Longitud del rayo desde un lado x a otro lado x.
		global->player.deltaDistY = fabs(1 / global->player.rayDirY); // Longitud del rayo desde un lado y a otro lado y.
		global->player.hit = 0;

		if (global->player.rayDirX < 0)
		{
			global->player.stepX = -1;
			global->player.sideDistX = (global->player.posX - global->player.mapX) * global->player.deltaDistX;
		}
		else
		{
			global->player.stepX = 1;
			global->player.sideDistX = (global->player.mapX + 1.0 - global->player.posX) * global->player.deltaDistX;
		}
		if (global->player.rayDirY < 0)
		{
			global->player.stepY = -1;
			global->player.sideDistY = (global->player.posY - global->player.mapY) * global->player.deltaDistY;
		}
		else
		{
			global->player.stepY = 1;
			global->player.sideDistY = (global->player.mapY + 1.0 - global->player.posY) * global->player.deltaDistY;
		}
		while (global->player.hit == 0)
		{
			if (global->player.sideDistX < global->player.sideDistY)
			{
				global->player.sideDistX += global->player.deltaDistX;
				global->player.mapX += global->player.stepX;
				global->player.side = 0;
			}
		else
		{
			global->player.sideDistY += global->player.deltaDistY;
			global->player.mapY += global->player.stepY;
			global->player.side = 1;
		}
		if (worldMap[global->player.mapX][global->player.mapY] > 0) 
			global->player.hit = 1;
		}
		if (global->player.side == 0)
		{
			global->player.perpWallDist = (global->player.mapX - global->player.posX + (1 - global->player.stepX) / 2) / global->player.rayDirX;
		}
		else
		{
			global->player.perpWallDist = (global->player.mapY - global->player.posY + (1 - global->player.stepY) / 2) / global->player.rayDirY;
		}
		global->player.line_height = (1080 / global->player.perpWallDist); // Calcula la altura de la linea a pintar.
		global->player.drawStart = -global->player.line_height / 2 + 1080 / 2;
		global->player.drawStart = (global->player.drawStart < 0) ? 0 : global->player.drawStart;
		global->player.drawEnd = global->player.line_height / 2 + 1080 / 2;
		global->player.drawEnd = (global->player.drawEnd >= 1080) ? 1080 - 1 : global->player.drawEnd;
		if (worldMap[global->player.mapX][global->player.mapY] == 1)
		{
			global->data.color = 0x665e48;
		}
		else if (worldMap[global->player.mapX][global->player.mapY] == 2)
		{
			global->data.color = 0x0000ff;
		}
		else
		{
			global->data.color = 0xffffff;
		}
		if (global->player.side == 1) // Esto es para darle un brillo diferente al chocar con una pared.
		{
			global->data.color = global->data.color / 2;
		}
		y = 0;
		while (y < global->player.drawStart) // Color del cielo.
		{
			my_mlx_pixel_put(&global->data, x, y, 0x2271b3);
			y++;
		}
		y = global->player.drawStart;
		while(y < global->player.drawEnd) // Color de la pared.
		{
			my_mlx_pixel_put(&global->data, x, y, global->data.color);
			y++;
		}
		while (y < 1080) //Color del suelo.
		{
			my_mlx_pixel_put(&global->data, x, y, 0x399c5d);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(global->data.mlx, global->data.win, global->data.img, 0, 0);
	return (1);
}

int main (void)
{
	t_global global;

	global.data.mlx		= mlx_init();
	global.data.win		= mlx_new_window(global.data.mlx, 1920, 1080, "Cub3d");
	global.data.img		= mlx_new_image(global.data.mlx, 1920, 1080);
	global.data.addr	= mlx_get_data_addr(global.data.img, &global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);

	// Asignación de valores.
	global.player.posX =	14;
	global.player.posY =	14;
	global.player.dirX =	-1;
	global.player.dirY =	0;
	global.player.planeX =	0;
	global.player.planeY =	0.66;

	mlx_hook(global.data.win, 02, (1L<<0), key_move, &global);
	mlx_loop_hook(global.data.mlx, raycasting, &global);
	mlx_loop(global.data.mlx);
}