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

void		ft_get_texture(t_global *global)
{
		/*	Guardar el valor obtenido de la funcion ft_fill_texture en el buffer para luego ser pintado	*/
		if (global->player.side == 0 && global->player.stepX == -1) // NORTE 
		{
			global->player.textura = global->textura_norte.tex_norte;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_norte.bits_per_pixel, &global->textura_norte.line_lenght, &global->textura_norte.endian);
		}
		if (global->player.side == 0 && global->player.stepX == 1) // SUR
		{
			global->player.textura = global->textura_sur.tex_sur;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_sur.bits_per_pixel, &global->textura_sur.line_lenght, &global->textura_sur.endian);
		}
		if (global->player.side == 1 && global->player.stepY == 1) // ESTE
		{
			global->player.textura = global->textura_este.tex_este;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_este.bits_per_pixel, &global->textura_este.line_lenght, &global->textura_este.endian);
		}
		if (global->player.side == 1 && global->player.stepY == -1) // OESTE
		{
			global->player.textura = global->textura_oeste.tex_oeste;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_oeste.bits_per_pixel, &global->textura_oeste.line_lenght, &global->textura_oeste.endian);
		}
}

void		ft_fill_texture(t_global *global)
{
	/* Asignar valor de textura a una variable "tex.norte/sur/este/oeste" */
	global->textura_norte.tex_norte = mlx_xpm_file_to_image(global->data.mlx, "srcs/wood.xpm", &global->player.tex_width, &global->player.tex_height);
	global->textura_sur.tex_sur = mlx_xpm_file_to_image(global->data.mlx, "srcs/madera.xpm", &global->player.tex_width, &global->player.tex_height);
	global->textura_este.tex_este = mlx_xpm_file_to_image(global->data.mlx, "srcs/mossy.xpm", &global->player.tex_width, &global->player.tex_height);
	global->textura_oeste.tex_oeste = mlx_xpm_file_to_image(global->data.mlx, "srcs/stone.xpm", &global->player.tex_width, &global->player.tex_height);
}

void		ft_init_structs(t_global *global)
{
	/*	Inicializar valores de variables en la estructura	*/

	global->player.posX =	4 - 0.5; /* Posicion inicial en x */
	global->player.posY =	4 + 0.5; /* Posicion inicial en y */
	global->player.dirX =	-1;
	global->player.dirY =	0;
	global->player.planeX =	0;
	global->player.planeY =	0.66;
	global->player.moveSpeed = 0.3; /* Movimiento del jugador */
	global->player.rotSpeed = 0.29; /* Movimiento de la camara */
}