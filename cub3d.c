/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:22 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/17 14:25:31 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int raycasting(t_global *global)
{
	int	w = global->mapa.width;
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
			if (global->mapa.memoria[global->player.mapX][global->player.mapY] == '1') 
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
		global->player.line_height = (global->mapa.height / global->player.perpWallDist); // Calcula la altura de la linea a pintar.
		global->player.drawStart = -global->player.line_height / 2 + global->mapa.height / 2;
		global->player.drawStart = (global->player.drawStart < 0) ? 0 : global->player.drawStart;
		global->player.drawEnd = global->player.line_height / 2 + global->mapa.height / 2;
		global->player.drawEnd = (global->player.drawEnd >= global->mapa.height) ? global->mapa.height - 1 : global->player.drawEnd;
	/*-------------------------------------------------------------------------------------------------------*/

		global->player.texNum = (int)global->mapa.memoria[global->player.mapX][global->player.mapY]; // DESDE AQUI EMPIEZAN LAS TEXTURAS.

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
		global->player.texPos = (global->player.drawStart - global->mapa.height / 2 + global->player.line_height / 2) * global->player.step;
		y = 0;
		while (y < global->player.drawStart) // Color del cielo.
		{
			my_mlx_pixel_put(&global->data, x, y, global->mapa.color_c);
			y++;
		}
		y = global->player.drawStart;
		ft_get_texture(global); // Funcion que le asigna valor a buffer (paredes).
		while (y++ < global->player.drawEnd)
		{
			global->player.texY = (int)global->player.texPos;
			global->player.texPos += global->player.step;
			global->data.color = global->player.buffer[global->player.tex_width * global->player.texY + global->player.texX]; 
			my_mlx_pixel_put(&global->data, x, y, global->data.color);
		}
		while (y < global->mapa.height) //Color del suelo.
		{
			my_mlx_pixel_put(&global->data, x, y, global->mapa.color_f);
			y++;
		}
		x++;
		/* AQUI EMPIEZA EL CASTING DE LOS SPRITES */
		/* AQUI TERMINA EL CASTING DE LOS SPRITES */
	}
	mlx_put_image_to_window(global->data.mlx, global->data.win, global->data.img, 0, 0);
	return (1);
}

int main (int argc, char **argv)
{
	t_global global;
	ft_init_structs(&global); // Inicializar valores
	ft_control_error(argc, argv);
	ft_parseo(&global, argv);
	
	global.data.mlx		= mlx_init();
	global.data.win		= mlx_new_window(global.data.mlx, global.mapa.width, global.mapa.height, "Cub3D");
	global.data.img		= mlx_new_image(global.data.mlx, global.mapa.width, global.mapa.height);
	global.data.addr	= mlx_get_data_addr(global.data.img, &global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);

	ft_fill_texture(&global); // Obtener texturas
	mlx_hook(global.data.win, 02, (0L<<0), key_move, &global); // Hook para las teclas
	mlx_loop_hook(global.data.mlx, raycasting, &global); // Loop del raycasting
	mlx_loop(global.data.mlx); // Loop general
}