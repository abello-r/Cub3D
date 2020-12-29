/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:16:48 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 18:38:08 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			raycasting5(t_global *global)
{
	if (global->player.side == 0)
	{
		global->player.perpwalldist = (global->player.map_x -
		global->player.pos_x + (1 - global->player.step_x) / 2) /
		global->player.ray_dir_x;
	}
	else
	{
		global->player.perpwalldist = (global->player.map_y -
		global->player.pos_y + (1 - global->player.step_y) / 2) /
		global->player.ray_dir_y;
	}
	global->player.line_height = (global->mapa.height /
	global->player.perpwalldist);
	global->player.draw_start = -global->player.line_height / 2 +
	global->mapa.height / 2;
	global->player.draw_start = (global->player.draw_start < 0) ? 0 :
	global->player.draw_start;
	global->player.draw_end = global->player.line_height / 2 +
	global->mapa.height / 2;
	global->player.draw_end = (global->player.draw_end >=
	global->mapa.height) ? global->mapa.height - 1 :
	global->player.draw_end;
	global->player.tex_num = (int)global->mapa.memoria
	[global->player.map_x][global->player.map_y];
}

void			raycasting6(t_global *global)
{
	if (global->player.side == 0)
	{
		global->player.wall_x = global->player.pos_y +
		global->player.perpwalldist * global->player.ray_dir_y;
	}
	else
		global->player.wall_x = global->player.pos_x +
		global->player.perpwalldist * global->player.ray_dir_x;
	global->player.wall_x -= floor((global->player.wall_x));
	global->player.tex_x = (int)(global->player.wall_x *
	(double)global->player.tex_width);
	if (global->player.side == 0 && global->player.ray_dir_x > 0)
		global->player.tex_x = global->player.tex_width -
		global->player.tex_x - 1;
	if (global->player.side == 1 && global->player.ray_dir_y < 0)
		global->player.tex_x = global->player.tex_width -
		global->player.tex_x - 1;
	global->player.step = 1.0 * global->player.tex_height /
	global->player.line_height;
	global->player.tex_pos = (global->player.draw_start -
	global->mapa.height / 2 + global->player.line_height / 2) *
	global->player.step;
}

void			raycasting7(t_global *global, int x, int y)
{
	y = -1;
	while (y++ < global->player.draw_start)
		my_mlx_pixel_put(global, x, y, global->mapa.color_c);
	y = global->player.draw_start;
	ft_get_texture(global);
	y--;
	while (y++ < global->player.draw_end)
	{
		global->player.tex_y = (int)global->player.tex_pos;
		global->player.tex_pos += global->player.step;
		global->data.color = global->player.buffer[global->player.tex_width
		* global->player.tex_y + global->player.tex_x];
		my_mlx_pixel_put(global, x, y, global->data.color);
	}
	y--;
	while (y < global->mapa.height)
	{
		my_mlx_pixel_put(global, x, y, global->mapa.color_f);
		y++;
	}
}
