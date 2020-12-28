/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:17:29 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/28 15:07:27 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			ft_res_sprites(t_global *global)
{
	int	i;

	i = 0;
	if (!(global->xysp = (t_xysp *)malloc(sizeof(t_xysp) * global->sprite.num)))
		ft_print_error("No hay memoria");
	if (!(global->sprite.z_buffer = (double *)malloc(sizeof(double) *
		(global->mapa.width + 1))))
		ft_print_error("No hay memoria");
	if (!(global->sprite.order = (int *)malloc(sizeof(int) *
		global->sprite.num + 1)))
		ft_print_error("No hay memoria");
}

void			ft_sort_sprites(t_global *global)
{
	int		i;

	i = -1;
	while (++i < global->sprite.num)
	{
		global->sprite.distance = sqrt((pow(global->xysp[i].x -
		global->player.posX, 2.0)) + pow(global->xysp[i].y
		- global->player.posY, 2.0));
		global->xysp[i].rel = global->sprite.distance;
	}
	ft_sort_sprites2(global);
}

void			ft_sort_sprites2(t_global *global)
{
	int		k;
	int		i;
	int		tmp;

	i = -1;
	while (++i < global->sprite.num - 1)
	{
		k = i + 1;
		while (k < global->sprite.num)
		{
			if (global->xysp[global->sprite.order[i]].rel <
				global->xysp[global->sprite.order[k]].rel)
			{
				tmp = global->sprite.order[i];
				global->sprite.order[i] = global->sprite.order[k];
				global->sprite.order[k] = tmp;
			}
			k++;
		}
	}
}

void			ft_ray_sprite(t_global *global)
{
	int		i;
	int		y;
	int		d;

	d = 0;
	y = 0;
	i = -1;
	while (++i < global->sprite.num)
	{
		global->sprite.order[i] = i;
		global->xysp[i].rel = ((global->player.posY - global->xysp[i].y) *
		(global->player.posY - global->xysp[i].y) + (global->player.posX -
		global->xysp[i].x) * (global->player.posX - global->xysp[i].x));
	}
	ft_sort_sprites(global);
	i = -1;
	while (++i < global->sprite.num)
	{
		ft_ray_sprite2(global, i);
		while (global->sprite.stripe < global->sprite.drawend_x)
		{
			ft_ray_sprite4(global, d, y);
			global->sprite.stripe++;
		}
	}
}

void			ft_ray_sprite2(t_global *global, int i)
{
	global->sprite.x = global->xysp[global->sprite.order[i]].x
	- global->player.posX;
	global->sprite.y = global->xysp[global->sprite.order[i]].y
	- global->player.posY;
	global->sprite.inv_det = 1.0 / (global->player.planeX *
	global->player.dirY - global->player.dirX * global->player.planeY);
	global->sprite.transform_x = global->sprite.inv_det * (global->player.dirY
	* global->sprite.x - global->player.dirX * global->sprite.y);
	global->sprite.transform_y = global->sprite.inv_det *
	(-global->player.planeY * global->sprite.x + global->player.planeX
	* global->sprite.y);
	global->sprite.sprite_screen_x = (int)(global->mapa.width / 2)
	* (1 + global->sprite.transform_x / global->sprite.transform_y);
	global->sprite.sprite_height =
	abs((int)(global->mapa.height / global->sprite.transform_y));
	global->sprite.drawstart_y =
	-global->sprite.sprite_height / 2 + global->mapa.height / 2;
	ft_ray_sprite3(global);
}
