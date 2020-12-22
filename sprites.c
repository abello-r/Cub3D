/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:17:29 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/22 18:40:21 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_res_sprites(t_global *global)
{
	int		i;
	
	i = 0;
	if(!(global->xysp = (t_xysp *)malloc(sizeof(t_xysp) * global->sprite.num)))
		ft_print_error("No hay memoria");
	if(!(global->sprite.z_buffer = (double *)malloc(sizeof(double) * (global->mapa.width + 1))))
		ft_print_error("No hay memoria");
	if(!(global->sprite.order = (int *)malloc(sizeof(int) * global->sprite.num + 1)))
		ft_print_error("No hay memoria");
}

void		ft_sort_sprites(t_global *global)
{
	int		i;
	int		j;
	int		k;
	int		tmp;

	i = 0;
	while (i < global->sprite.num)
	{
		global->sprite.distance = sqrt((pow(global->xysp[i].x - global->player.posX, 2.0)) + pow(global->xysp[i].y - global->player.posY, 2.0));
		global->xysp[i].rel = global->sprite.distance;
		i++;
	}
	j = 0;
	while (j < global->sprite.num - 1)
	{
		k = j + 1;
		while (k < global->sprite.num)
		{
			if (global->xysp[global->sprite.order[j]].rel < global->xysp[global->sprite.order[k]].rel)
			{
				tmp = global->sprite.order[j];
				global->sprite.order[j] = global->sprite.order[k];
				global->sprite.order[k] = tmp;
			}
			k++;
		}
		j++;
	}
}

void		ft_ray_sprite(t_global *global)
{
	int		i;
	int		y;
	int		d;

	d = 0;
	y = 0;
	i = 0;
	while (i  < global->sprite.num)
	{
		global->sprite.order[i] = i;
		global->xysp[i].rel = ((global->player.posY - global->xysp[i].y) * (global->player.posY - global->xysp[i].y) + (global->player.posX - global->xysp[i].x) * (global->player.posX - global->xysp[i].x));
		i++;
	}
	ft_sort_sprites(global);
	i = 0;
	while (i < global->sprite.num)
	{
		global->sprite.x = global->xysp[global->sprite.order[i]].x - global->player.posX;
		global->sprite.y = global->xysp[global->sprite.order[i]].y - global->player.posY;
		global->sprite.inv_det = 1.0 / (global->player.planeX * global->player.dirY - global->player.dirX * global->player.planeY);
		global->sprite.transform_x = global->sprite.inv_det * (global->player.dirY * global->sprite.x - global->player.dirX * global->sprite.y);
		global->sprite.transform_y = global->sprite.inv_det * (-global->player.planeY * global->sprite.x + global->player.planeX * global->sprite.y);
		global->sprite.sprite_screen_x = (int)(global->mapa.width / 2) * (1 + global->sprite.transform_x / global->sprite.transform_y);
		global->sprite.sprite_height = abs((int)(global->mapa.height / global->sprite.transform_y));
		global->sprite.drawstart_y = -global->sprite.sprite_height / 2 + global->mapa.height / 2;

		if (global->sprite.drawstart_y < 0)
			global->sprite.drawstart_y = 0;
		global->sprite.drawend_y = global->sprite.sprite_height / 2 + global->mapa.height / 2;
		if (global->sprite.drawend_y >= global->mapa.height)
			global->sprite.drawend_y = global->mapa.height - 1;
		global->sprite.sprite_width = abs((int)(global->mapa.height / global->sprite.transform_y));
		global->sprite.drawstart_x = -global->sprite.sprite_width / 2 + global->sprite.sprite_screen_x;
		if (global->sprite.drawstart_x < 0)
			global->sprite.drawstart_x = 0; 
		global->sprite.drawend_x = global->sprite.sprite_width / 2 + global->sprite.sprite_screen_x;
		if (global->sprite.drawend_x >= global->mapa.width)
			global->sprite.drawend_x = global->mapa.width - 1;
		global->sprite.stripe = global->sprite.drawstart_x;

		while (global->sprite.stripe < global->sprite.drawend_x)
		{
			global->sprite.tex_x = (int)(256 * (global->sprite.stripe - (-global->sprite.sprite_width / 2 +  
				global->sprite.sprite_screen_x)) * global->sprite.tex_width / global->sprite.sprite_width) / 256;
			if (global->sprite.transform_y > 0 && global->sprite.stripe > 0 && global->sprite.stripe < global->mapa.width && global->sprite.transform_y < global->sprite.z_buffer[global->sprite.stripe])
			{
				y = global->sprite.drawstart_y;
				while (y < (global->sprite.drawend_y))
				{
					d = (y) * 256 - global->mapa.height * 128 + global->sprite.sprite_height * 128;
					global->sprite.tex_y = ((d * global->sprite.tex_height) / global->sprite.sprite_height) / 256;
					global->data.color = global->sprite.buffer[global->sprite.tex_height *  global->sprite.tex_y + global->sprite.tex_x];
					if (global->data.color != 0)
						my_mlx_pixel_put(global, global->sprite.stripe, y, global->data.color);
					y++;
				}
			}
			global->sprite.stripe++;
		}
		i++;
	}
}