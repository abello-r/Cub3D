/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:07:05 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/28 15:08:07 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			ft_ray_sprite3(t_global *global)
{
	if (global->sprite.drawstart_y < 0)
		global->sprite.drawstart_y = 0;
	global->sprite.drawend_y = global->sprite.sprite_height / 2 +
	global->mapa.height / 2;
	if (global->sprite.drawend_y >= global->mapa.height)
		global->sprite.drawend_y = global->mapa.height - 1;
	global->sprite.sprite_width = abs((int)(global->mapa.height /
	global->sprite.transform_y));
	global->sprite.drawstart_x = -global->sprite.sprite_width / 2 +
	global->sprite.sprite_screen_x;
	if (global->sprite.drawstart_x < 0)
		global->sprite.drawstart_x = 0;
	global->sprite.drawend_x = global->sprite.sprite_width / 2 +
	global->sprite.sprite_screen_x;
	if (global->sprite.drawend_x >= global->mapa.width)
		global->sprite.drawend_x = global->mapa.width - 1;
	global->sprite.stripe = global->sprite.drawstart_x;
}

void			ft_ray_sprite4(t_global *global, int d, int y)
{
	global->sprite.tex_x = (int)(256 * (global->sprite.stripe -
	(-global->sprite.sprite_width / 2 + global->sprite.sprite_screen_x)) *
	global->sprite.tex_width / global->sprite.sprite_width) / 256;
	if (global->sprite.transform_y > 0 && global->sprite.stripe > 0 &&
	global->sprite.stripe < global->mapa.width && global->sprite.transform_y
	< global->sprite.z_buffer[global->sprite.stripe])
	{
		y = global->sprite.drawstart_y;
		while (y < (global->sprite.drawend_y))
		{
			d = (y) * 256 - global->mapa.height * 128 +
			global->sprite.sprite_height * 128;
			global->sprite.tex_y = ((d * global->sprite.tex_height) /
			global->sprite.sprite_height) / 256;
			global->data.color = global->sprite.buffer[global->sprite.tex_height
			* global->sprite.tex_y + global->sprite.tex_x];
			if (global->data.color != 0)
				my_mlx_pixel_put(global, global->sprite.stripe, y,
				global->data.color);
			y++;
		}
	}
}
