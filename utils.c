/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:16 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/27 17:20:20 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*---------------------------------------------------- Insertar pixel más rapido que la original */

void	my_mlx_pixel_put(t_global *global, int x, int y, int color)
{
	char *dst;

	dst = (char *)global->data.addr + (y * global->data.line_lenght + x * (global->data.bits_per_pixel / 8));
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
		if (global->mapa.memoria[(int)(global->player.posX + global->player.dirX * global->player.moveSpeed)][((int)global->player.posY)] == '0')
		{
			global->player.posX += global->player.dirX * global->player.moveSpeed;
		}
		if (global->mapa.memoria[(int)global->player.posX][(int)(global->player.posY + global->player.dirY * global->player.moveSpeed)] == '0')
		{
			global->player.posY += global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_DOWN) // Mover Abajo REVISADA
	{
		if (global->mapa.memoria[(int)(global->player.posX - global->player.dirX * global->player.moveSpeed)][(int)global->player.posY] == '0')
		{
			global->player.posX -= global->player.dirX * global->player.moveSpeed;
		} 
		if (global->mapa.memoria[(int)global->player.posX][(int)(global->player.posY - global->player.dirY * global->player.moveSpeed)] == '0')
		{
			global->player.posY -= global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_RIGHT) // Mover derecha REVISADA
	{
		if (global->mapa.memoria[(int)(global->player.posX)][((int)(global->player.posY - global->player.dirX * global->player.moveSpeed))] == '0')
		{
			global->player.posY -= global->player.dirX * global->player.moveSpeed;
		}
		if (global->mapa.memoria[(int)(global->player.posX + global->player.dirY * global->player.moveSpeed)][(int)(global->player.posY)] == '0')
		{
			global->player.posX += global->player.dirY * global->player.moveSpeed;
		}
	}
	if (keycode == KEY_LEFT) // Mover Izquierda REVISADA
	{
		if (global->mapa.memoria[(int)(global->player.posX)][((int)(global->player.posY + global->player.dirX * global->player.moveSpeed))] == '0')
		{
			global->player.posY += global->player.dirX * global->player.moveSpeed;
		}
		if (global->mapa.memoria[(int)(global->player.posX - global->player.dirY * global->player.moveSpeed)][(int)(global->player.posY)] == '0')
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
			global->player.tex_width = global->textura_norte.tex_width;
			global->player.tex_height = global->textura_norte.tex_height;
			global->player.textura = global->textura_norte.tex_norte;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_norte.bits_per_pixel, &global->textura_norte.line_lenght, &global->textura_norte.endian);
		}
		if (global->player.side == 0 && global->player.stepX == 1) // SUR
		{
			global->player.tex_width = global->textura_sur.tex_width;
			global->player.tex_height = global->textura_sur.tex_height;
			global->player.textura = global->textura_sur.tex_sur;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_sur.bits_per_pixel, &global->textura_sur.line_lenght, &global->textura_sur.endian);
		}
		if (global->player.side == 1 && global->player.stepY == 1) // ESTE
		{
			global->player.tex_width = global->textura_este.tex_width;
			global->player.tex_height = global->textura_este.tex_height;
			global->player.textura = global->textura_este.tex_este;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_este.bits_per_pixel, &global->textura_este.line_lenght, &global->textura_este.endian);
		}
		if (global->player.side == 1 && global->player.stepY == -1) // OESTE
		{
			global->player.tex_width = global->textura_oeste.tex_width;
			global->player.tex_height = global->textura_oeste.tex_height;
			global->player.textura = global->textura_oeste.tex_oeste;
			global->player.buffer = (unsigned int *)mlx_get_data_addr(global->player.textura, &global->textura_oeste.bits_per_pixel, &global->textura_oeste.line_lenght, &global->textura_oeste.endian);
		}
	global->sprite.buffer = (unsigned int *)mlx_get_data_addr(global->sprite.tex_add, &global->sprite.bits_per_pixel, &global->sprite.line_lenght, &global->sprite.endian);
}

void		ft_fill_texture(t_global *global)
{
	if (!(global->textura_norte.tex_norte = mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_norte, &global->textura_norte.tex_width, &global->textura_norte.tex_height)))
		ft_print_error("La textura NORTE que has introducido no existe.");
	else if (!(global->textura_sur.tex_sur = mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_sur, &global->textura_sur.tex_width, &global->textura_sur.tex_height)))
		ft_print_error("La textura SUR que has introducido no existe.");
	else if (!(global->textura_oeste.tex_oeste = mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_este, &global->textura_oeste.tex_width, &global->textura_oeste.tex_height)))
		ft_print_error("La textura OESTE que has introducido no existe.");
	else if (!(global->textura_este.tex_este = mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_oeste, &global->textura_este.tex_width, &global->textura_este.tex_height)))
		ft_print_error("La textura ESTE que has introducido no existe.");
	if (!(global->sprite.tex_add = mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_sprite, &global->sprite.tex_width, &global->sprite.tex_height)))
		ft_print_error("La textura del SPRITE no existe");
}

void		ft_init_structs(t_global *global)
{
	global->player.dirX = -1;
	global->player.dirY = 0;
	global->player.planeX = 0;
	global->player.planeY = 0.66;
	global->player.moveSpeed = 0.27;
	global->player.rotSpeed = 0.14;
	global->mapa.ruta_norte = NULL;
	global->mapa.ruta_sur = NULL;
	global->mapa.ruta_este = NULL;
	global->mapa.ruta_oeste = NULL;
	global->mapa.ruta_sprite = NULL;
	global->mapa.tmp1 = NULL;
	global->mapa.tmp2 = NULL;
	global->mapa.xpvu = 0;
	global->sprite.num = 0;
}

void		ft_init_structs2(t_global *global)
{
	global->arg.r =		0;
	global->arg.n =		0;
	global->arg.so =	0;
	global->arg.w =		0;
	global->arg.e =		0;
	global->arg.s =		0;
	global->arg.f =		0;
	global->arg.c =		0;
	global->arg.map =	0;
}

int		ft_control_error(t_global *global, int argc, char **argv)
{
	char	*tmp;
	int		i;

	i = 0;
	if (argc < 2 || argc > 3)
		ft_print_error("Número de argumentos inválido.");
	else if (argc == 2 || argc == 3)
	{
		if ((tmp = ft_strchr(argv[1], '.')) == NULL)
			ft_print_error("Argumento inválido : Revisa que el archivo termine en \".cub\".");
		if ((ft_strncmp(tmp, ".cub\0", 5)) != 0)
			ft_print_error("Argumento inválido : Revisa que el archivo termine en \".cub\".");
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save\0", 7) != 0)
				ft_print_error("Argumento inválido : Prueba escribiendo \"--save\".");
			else
			{
				raycasting(global);
				ft_screenshot(global);
			}
		}
	}
	return (0);
}

void		ft_print_error(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	exit(0);
}

int		ft_parseo(t_global *global, char **argv)
{
	char	*line;
	int		fd;
	int		x;

	x = 0;
	line = NULL;
	global->mapa.i = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_print_error("El archivo \".cub\" que intentas abrir no existe.");
	while ((global->mapa.i = get_next_line(fd, &line)) > 0)
	{
		ft_check_lines(global, line);
		free(line);
		line = NULL;
		x++;
	}
	ft_check_lines(global, line);
	ft_no_repeat(global);
	close(fd);
	free(line);
	line = NULL;
	ft_reservar_map(global);
	ft_fill_map(global, argv);
	return (0);
}

int		ft_check_lines(t_global *global, char *line)
{
	int i;
	int x;

	x = 1;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
	{
		global->mapa.tmp1 = line;
		ft_check_resolucion(global, x);
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
		ft_check_ruta_norte(global, line);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		ft_check_ruta_sur(global, line);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		ft_check_ruta_este(global, line);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		ft_check_ruta_oeste(global, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		ft_check_ruta_sprite(global, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_check_color_f(global, line);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_check_color_c(global, line);
	else if (line[i] == ' ' || line[i] == '0'
		|| line[i] == '1' || line[i] == '2')
		ft_check_map(global, line);
	else if (global->mapa.xpvu > 0 || global->mapa.old > 0)
	{
		if (line[i] == '\0')
			ft_print_error("Mapa separado por saltos de línea");
		if (ft_isascii(line[i]))
			ft_print_error("Hay un carácter inválido despúes del mapa");
	}
	return (0);  // Hacer un flag por cada argumento 1 si es correcto 2 si hay mas de uno y 0 si no hay
}

int			ft_is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int		ft_exit(t_global *global)
{
	mlx_destroy_window(global->data.mlx, global->data.win);
	exit(0);
	return (0);
}

void		ft_no_repeat(t_global *global)
{
	if (global->arg.r == 0 || global->arg.r == 2)
		ft_print_error("No hay resolución ó está duplicada");
	if (global->arg.n == 2)
		ft_print_error("La textura NORTE está duplicada");
	if (global->arg.so == 2)
		ft_print_error("La textura SUR está duplicada");
	if (global->arg.w == 2)
		ft_print_error("La textura OESTE está duplicada");
	if (global->arg.e == 2)
		ft_print_error("La textura ESTE está duplicada");
	if (global->arg.s == 2)
		ft_print_error("La ruta al SPRITE está duplicada");
	if (global->arg.c == 0 || global->arg.c == 2)
		ft_print_error("No hay color del cielo ó está duplicado");
	if (global->arg.f == 0 || global->arg.f == 2)
		ft_print_error("No hay color del suelo ó está duplicado");
}