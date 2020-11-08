#include "mini.h"

/*---------------------------------------------------- Insertar pixel más rapido que la original */

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*---------------------------------------------------- Movimiento dentro del cub3d */

int		key_move(int keycode, t_global *global)
{
	global->player.moveSpeed = 0.6; // Aumentando el 0.1 damos más velocidad al movimiento vectorial.
	global->player.rotSpeed = 0.1 * 3.0; // Aquí pasa igual pero con el movimiento de rotación.
	printf("%d\n", keycode);

	if (keycode == ESCAPE) // Escape REVISADA
	{
		mlx_clear_window(global->data.mlx, global->data.win);
		mlx_destroy_window(global->data.mlx, global->data.win);
		exit(0);
	}

	if (keycode == KEY_UP) // Mover Arriba REVISADA
	{
		if (!worldMap[(int)(global->player.posX + global->player.dirX * global->player.moveSpeed)][((int)global->player.posY)])
		{
			global->player.posX += global->player.dirX * global->player.moveSpeed;
		}
		if (!worldMap[(int)global->player.posX][(int)(global->player.posY + global->player.dirY * global->player.moveSpeed)])
		{
			global->player.posY += global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_DOWN) // Mover Abajo REVISADA
	{
		if (!worldMap[(int)(global->player.posX - global->player.dirX * global->player.moveSpeed)][(int)global->player.posY])
		{
			global->player.posX -= global->player.dirX * global->player.moveSpeed;
		} 
		if (!worldMap[(int)global->player.posX][(int)(global->player.posY - global->player.dirY * global->player.moveSpeed)])
		{
			global->player.posY -= global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_RIGHT) // Mover derecha REVISADA
	{
		if (!worldMap[(int)(global->player.posX)][((int)(global->player.posY - global->player.dirX * global->player.moveSpeed))])
		{
			global->player.posY -= global->player.dirX * global->player.moveSpeed;
		}
		if (!worldMap[(int)(global->player.posX + global->player.dirY * global->player.moveSpeed)][(int)(global->player.posY)])
		{
			global->player.posX += global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_LEFT) // Mover Izquierda REVISADA
	{
		if (!worldMap[(int)(global->player.posX)][((int)(global->player.posY + global->player.dirX * global->player.moveSpeed))])
		{
			global->player.posY += global->player.dirX * global->player.moveSpeed;
		}
		if (!worldMap[(int)(global->player.posX - global->player.dirY * global->player.moveSpeed)][(int)(global->player.posY)])
		{
			global->player.posX -= global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_RIGHT_VISION) // Rotar a la Derecha REVISADA
	{
		global->player.oldDirX = global->player.dirX;
		global->player.dirX = global->player.dirX * cos(-global->player.rotSpeed) - global->player.dirY * sin(-global->player.rotSpeed);
		global->player.dirY = global->player.oldDirX * sin(-global->player.rotSpeed) + global->player.dirY * cos(-global->player.rotSpeed);
		global->player.oldPlaneX = global->player.planeX;
		global->player.planeX = global->player.planeX * cos(-global->player.rotSpeed) - global->player.planeY * sin(-global->player.rotSpeed);
		global->player.planeY = global->player.oldPlaneX * sin(-global->player.rotSpeed) + global->player.planeY * cos(-global->player.rotSpeed);
	}
	if (keycode == KEY_LEFT_VISION) // Rotar a la Izquierda REVISADA
	{
		global->player.oldDirX = global->player.dirX;
		global->player.dirX = global->player.dirX * cos(global->player.rotSpeed) - global->player.dirY * sin(global->player.rotSpeed);
		global->player.dirY = global->player.oldDirX * sin(global->player.rotSpeed) + global->player.dirY * cos(global->player.rotSpeed);
		global->player.oldPlaneX = global->player.planeX;
		global->player.planeX = global->player.planeX * cos(global->player.rotSpeed) - global->player.planeY * sin(global->player.rotSpeed);
		global->player.planeY = global->player.oldPlaneX * sin(global->player.rotSpeed) + global->player.planeY * cos(global->player.rotSpeed);
	}
	return (0);
}

/*----------------------------------------------------*/

void		ft_getTexture(t_global *global)
{

		global->player.stepX = -1; // ESTO NO DEBERIA ESTAR. 
		
		if (global->player.side == 0 && global->player.stepX == -1) // NORTE 
		{
			global->player.textura = mlx_xpm_file_to_image(global->data.mlx, "srcs/wood.xpm", &global->player.tex_width, &global->player.tex_height);
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_norte.bits_per_pixel, &global->textura_norte.line_lenght, &global->textura_norte.endian);
		}
		if (global->player.side == 0 && global->player.stepX == 1) // SUR
		{
			global->player.textura = mlx_xpm_file_to_image(global->data.mlx, "srcs/stone.xpm", &global->player.tex_width, &global->player.tex_height);
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_sur.bits_per_pixel, &global->textura_sur.line_lenght, &global->textura_sur.endian);
		}
		if (global->player.side == 1 && global->player.stepY == 1) // ESTE
		{
			global->player.textura = mlx_xpm_file_to_image(global->data.mlx, "srcs/mossy.xpm", &global->player.tex_width, &global->player.tex_height);
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_este.bits_per_pixel, &global->textura_este.line_lenght, &global->textura_este.endian);
		}
		if (global->player.side == 1 && global->player.stepY == -1) // OESTE
		{
			global->player.textura = mlx_xpm_file_to_image(global->data.mlx, "srcs/redbrick.xpm", &global->player.tex_width, &global->player.tex_height);
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_oeste.bits_per_pixel, &global->textura_oeste.line_lenght, &global->textura_oeste.endian);
		}
}

/*----------------------------------------------------*/