/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:22 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 20:26:45 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int					raycasting(t_global *global)
{
	int	w;
	int x;
	int y;

	w = global->mapa.width;
	x = 0;
	y = 0;
	while (x < w)
	{
		raycasting2(global, x, w);
		raycasting3(global);
		raycasting4(global);
		raycasting5(global);
		raycasting6(global);
		raycasting7(global, x, y);
		global->sprite.z_buffer[x] = global->player.perpwalldist;
		x++;
	}
	ft_ray_sprite(global);
	mlx_put_image_to_window(global->data.mlx, global->data.win,
	global->data.img, 0, 0);
	key_move(global);
	return (1);
}

void				raycasting2(t_global *global, int x, int w)
{
	global->player.camera_x = 2 * x / (double)w - 1;
	global->player.ray_dir_x = global->player.dir_x + global->player.plane_x
	* global->player.camera_x;
	global->player.ray_dir_y = global->player.dir_y + global->player.plane_y
	* global->player.camera_x;
	global->player.map_x = (int)global->player.pos_x;
	global->player.map_y = (int)global->player.pos_y;
	global->player.delta_dist_x = fabs(1 / global->player.ray_dir_x);
	global->player.delta_dist_y = fabs(1 / global->player.ray_dir_y);
	global->player.hit = 0;
}

void				raycasting3(t_global *global)
{
	if (global->player.ray_dir_x < 0)
	{
		global->player.step_x = -1;
		global->player.side_dist_x = (global->player.pos_x -
		global->player.map_x) * global->player.delta_dist_x;
	}
	else
	{
		global->player.step_x = 1;
		global->player.side_dist_x = (global->player.map_x + 1.0 -
		global->player.pos_x) * global->player.delta_dist_x;
	}
	if (global->player.ray_dir_y < 0)
	{
		global->player.step_y = -1;
		global->player.side_dist_y = (global->player.pos_y -
		global->player.map_y) * global->player.delta_dist_y;
	}
	else
	{
		global->player.step_y = 1;
		global->player.side_dist_y = (global->player.map_y + 1.0 -
		global->player.pos_y) * global->player.delta_dist_y;
	}
}

void				raycasting4(t_global *global)
{
	while (global->player.hit == 0)
	{
		if (global->player.side_dist_x < global->player.side_dist_y)
		{
			global->player.side_dist_x += global->player.delta_dist_x;
			global->player.map_x += global->player.step_x;
			global->player.side = 0;
		}
		else
		{
			global->player.side_dist_y += global->player.delta_dist_y;
			global->player.map_y += global->player.step_y;
			global->player.side = 1;
		}
		if (global->mapa.memoria[global->player.map_x]
		[global->player.map_y] == '1')
			global->player.hit = 1;
	}
}

int					main(int argc, char **argv)
{
	t_global global;

	ft_init_structs(&global);
	ft_init_structs2(&global);
	ft_parseo(&global, argv);
	global.data.mlx = mlx_init();
	global.data.win = mlx_new_window(global.data.mlx, global.mapa.width,
	global.mapa.height, "Cub3D");
	global.data.img = mlx_new_image(global.data.mlx, global.mapa.width,
	global.mapa.height);
	global.data.addr = mlx_get_data_addr(global.data.img,
	&global.data.bits_per_pixel, &global.data.line_lenght, &global.data.endian);
	ft_fill_texture(&global);
	ft_control_error(&global, argc, argv);
	mlx_hook(global.data.win, 02, (0L << 0), key_press, &global);
	mlx_hook(global.data.win, 03, (0L << 0), key_release, &global);
	mlx_hook(global.data.win, 17, (17L << 0), ft_exit, &global);
	mlx_loop_hook(global.data.mlx, raycasting, &global);
	mlx_loop(global.data.mlx);
}
