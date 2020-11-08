#include "mini.h"

int worldMap [mapWidth] [mapHeight] = 
{ {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7}, 
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, 
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, 
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7}, 
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7}, 
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7}, 
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1}, 
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1}, 
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8}, 
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1}, 
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1}, 
  {6,6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6}, 
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4}, 
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6}, 
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3}, 
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2}, 
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2}, 
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2}, 
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2}, 
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2}, 
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2}, 
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3} 
} ;

int raycasting(t_global *global)
{
	int	w = screenWidth;
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
		global->player.line_height = (screenHeight / global->player.perpWallDist); // Calcula la altura de la linea a pintar.
		global->player.drawStart = -global->player.line_height / 2 + screenHeight / 2;
		global->player.drawStart = (global->player.drawStart < 0) ? 0 : global->player.drawStart;
		global->player.drawEnd = global->player.line_height / 2 + screenHeight / 2;
		global->player.drawEnd = (global->player.drawEnd >= screenHeight) ? screenHeight - 1 : global->player.drawEnd;
	/*-------------------------------------------------------------------------------------------------------*/

		global->player.texNum = worldMap[global->player.mapX][global->player.mapY]; // DESDE AQUI

		if (global->player.side == 0)
		{
			global->player.wallX = global->player.posY + global->player.perpWallDist * global->player.rayDirY;
		}
		else 
		{
			global->player.wallX = global->player.posX + global->player.perpWallDist * global->player.rayDirX;
		}
		global->player.wallX -= floor((global->player.wallX));
		global->player.texX = (int)(global->player.wallX * (double)global->player.tex_width);
		if (global->player.side == 0 && global->player.rayDirX > 0)
		{
			global->player.texX = global->player.tex_width - global->player.texX - 1;
		}
		if (global->player.side == 1 && global->player.rayDirY < 0)
		{
			global->player.texX = global->player.tex_width - global->player.texX - 1;
		}
		global->player.step = 1.0 * global->player.tex_height / global->player.line_height;
		global->player.texPos = (global->player.drawStart - screenHeight / 2 + global->player.line_height / 2) * global->player.step;
		y = 0;
		while (y < global->player.drawStart) // Color del cielo.
		{
			my_mlx_pixel_put(&global->data, x, y, 0x2271b3);
			y++;
		}
		y = global->player.drawStart;
		while (y++ < global->player.drawEnd)
		{
			global->player.texY = (int)global->player.texPos;
			global->player.texPos += global->player.step;
			//FUNCION DE SELECCIONAR TEXTURA DEPENDE DE LA ORIENTACION.
			global->data.color = global->player.buffer[global->player.tex_width * global->player.texY + global->player.texX]; 
			my_mlx_pixel_put(&global->data, x, y, global->data.color);
		}
		while (y < screenHeight) //Color del suelo.
		{
			my_mlx_pixel_put(&global->data, x, y, 0x399c5d);
			y++;
		}
		/*-----------------------------------------------------------------------------------------------------------------------------*/
		
		/*if (worldMap[global->player.mapX][global->player.mapY] == 1)
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
		y = global->player.drawStart;
		while(y < global->player.drawEnd) // Color de la pared.
		{
			my_mlx_pixel_put(&global->data, x, y, global->data.color);
			y++;
		}
		}*/
		x++;
	}
	mlx_put_image_to_window(global->data.mlx, global->data.win, global->data.img, 0, 0);
	return (1);
}

int main (void)
{
	t_global global;

	global.data.mlx		= mlx_init();
	global.data.win		= mlx_new_window(global.data.mlx, screenWidth, screenHeight, "Cub3d");
	global.data.img		= mlx_new_image(global.data.mlx, screenWidth, screenHeight);
	global.data.addr	= mlx_get_data_addr(global.data.img, &global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);

	// Asignación de valores.
	global.player.posX =	14 - 0.5;
	global.player.posY =	14 + 0.5;
	global.player.dirX =	-1;
	global.player.dirY =	0;
	global.player.planeX =	0;
	global.player.planeY =	0.66;

	mlx_hook(global.data.win, 02, (1L<<0), key_move, &global);
	mlx_loop_hook(global.data.mlx, raycasting, &global);
	ft_getTexture(&global);
	mlx_loop(global.data.mlx);
}