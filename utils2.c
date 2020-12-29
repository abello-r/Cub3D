/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:14:03 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 17:05:47 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		key_move2(t_global *global)
{
	if (global->mapa.memoria[(int)(global->player.pos_x +
	global->player.dir_x * global->player.move_speed)]
	[((int)global->player.pos_y)] == '0')
		global->player.pos_x += global->player.dir_x *
		global->player.move_speed;
	if (global->mapa.memoria[(int)global->player.pos_x]
	[(int)(global->player.pos_y + global->player.dir_y *
	global->player.move_speed)] == '0')
		global->player.pos_y += global->player.dir_y *
		global->player.move_speed;
}

void		key_move3(t_global *global)
{
	if (global->mapa.memoria[(int)(global->player.pos_x -
	global->player.dir_x * global->player.move_speed)]
	[(int)global->player.pos_y] == '0')
		global->player.pos_x -= global->player.dir_x *
		global->player.move_speed;
	if (global->mapa.memoria[(int)global->player.pos_x]
	[(int)(global->player.pos_y - global->player.dir_y *
	global->player.move_speed)] == '0')
		global->player.pos_y -= global->player.dir_y *
		global->player.move_speed;
}

void		key_move4(t_global *global)
{
	if (global->mapa.memoria[(int)(global->player.pos_x)]
	[((int)(global->player.pos_y - global->player.dir_x *
	global->player.move_speed))] == '0')
		global->player.pos_y -= global->player.dir_x *
		global->player.move_speed;
	if (global->mapa.memoria[(int)(global->player.pos_x +
	global->player.dir_y * global->player.move_speed)]
	[(int)(global->player.pos_y)] == '0')
		global->player.pos_x += global->player.dir_y *
		global->player.move_speed;
}

void		key_move5(t_global *global)
{
	if (global->mapa.memoria[(int)(global->player.pos_x)]
	[((int)(global->player.pos_y + global->player.dir_x *
		global->player.move_speed))] == '0')
		global->player.pos_y += global->player.dir_x *
		global->player.move_speed;
	if (global->mapa.memoria[(int)(global->player.pos_x -
	global->player.dir_y * global->player.move_speed)]
	[(int)(global->player.pos_y)] == '0')
		global->player.pos_x -= global->player.dir_y
		* global->player.move_speed;
}

void		key_vision_right(t_global *global)
{
	global->player.old_dir_x = global->player.dir_x;
	global->player.dir_x = global->player.dir_x *
	cos(-global->player.rot_speed) - global->player.dir_y *
	sin(-global->player.rot_speed);
	global->player.dir_y = global->player.old_dir_x *
	sin(-global->player.rot_speed) + global->player.dir_y *
	cos(-global->player.rot_speed);
	global->player.old_plane_x = global->player.plane_x;
	global->player.plane_x = global->player.plane_x *
	cos(-global->player.rot_speed) - global->player.plane_y *
	sin(-global->player.rot_speed);
	global->player.plane_y = global->player.old_plane_x *
	sin(-global->player.rot_speed) + global->player.plane_y *
	cos(-global->player.rot_speed);
}
