/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:21:27 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/30 19:20:06 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			key_vision_left(t_global *global)
{
	global->player.old_dir_x = global->player.dir_x;
	global->player.dir_x = global->player.dir_x * cos(global->player.rot_speed)
	- global->player.dir_y * sin(global->player.rot_speed);
	global->player.dir_y = global->player.old_dir_x *
	sin(global->player.rot_speed) + global->player.dir_y *
	cos(global->player.rot_speed);
	global->player.old_plane_x = global->player.plane_x;
	global->player.plane_x = global->player.plane_x *
	cos(global->player.rot_speed) - global->player.plane_y *
	sin(global->player.rot_speed);
	global->player.plane_y = global->player.old_plane_x *
	sin(global->player.rot_speed) + global->player.plane_y *
	cos(global->player.rot_speed);
}

void			ft_get_texture2(t_global *global)
{
	if (global->player.side == 1 && global->player.step_y == 1)
	{
		global->player.tex_width = global->textura_este.tex_width;
		global->player.tex_height = global->textura_este.tex_height;
		global->player.textura = global->textura_este.tex_este;
		global->player.buffer = (unsigned int *)
		mlx_get_data_addr(global->player.textura,
		&global->textura_este.bits_per_pixel,
		&global->textura_este.line_lenght, &global->textura_este.endian);
	}
	if (global->player.side == 1 && global->player.step_y == -1)
	{
		global->player.tex_width = global->textura_oeste.tex_width;
		global->player.tex_height = global->textura_oeste.tex_height;
		global->player.textura = global->textura_oeste.tex_oeste;
		global->player.buffer = (unsigned int *)
		mlx_get_data_addr(global->player.textura,
		&global->textura_oeste.bits_per_pixel,
		&global->textura_oeste.line_lenght, &global->textura_oeste.endian);
	}
	global->sprite.buffer = (unsigned int *)
	mlx_get_data_addr(global->sprite.tex_add, &global->sprite.bits_per_pixel,
	&global->sprite.line_lenght, &global->sprite.endian);
}

void			ft_check_lines2(t_global *global, char *line, int i)
{
	if (line[i] == 'S' && line[i + 1] == 'O')
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
	else if (ft_strchr(ALPN, line[i]))
		if (line[i] != '\0' && line[i] != ' ')
			ft_print_error("Carácter inválido en la sección de texturas");
}

int				ft_exit(t_global *global)
{
	mlx_destroy_window(global->data.mlx, global->data.win);
	exit(0);
	return (0);
}

void			ft_no_repeat(t_global *global)
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
