/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:49:31 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 20:29:37 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int				key_press(int keycode, t_global *global)
{
	if (keycode == ESCAPE)
	{
		mlx_clear_window(global->data.mlx, global->data.win);
		mlx_destroy_window(global->data.mlx, global->data.win);
		exit(0);
	}
	if (keycode == KEY_UP && global->data.w == 0)
		global->data.w = 1;
	if (keycode == KEY_DOWN && global->data.s == 0)
		global->data.s = 1;
	if (keycode == KEY_RIGHT && global->data.d == 0)
		global->data.d = 1;
	if (keycode == KEY_LEFT && global->data.a == 0)
		global->data.a = 1;
	if (keycode == KEY_RIGHT_VISION && global->data.right == 0)
		global->data.right = 1;
	if (keycode == KEY_LEFT_VISION && global->data.left == 0)
		global->data.left = 1;
	return (0);
}

int				key_release(int keycode, t_global *global)
{
	if (keycode == KEY_UP && global->data.w == 1)
		global->data.w = 0;
	if (keycode == KEY_DOWN && global->data.s == 1)
		global->data.s = 0;
	if (keycode == KEY_RIGHT && global->data.d == 1)
		global->data.d = 0;
	if (keycode == KEY_LEFT && global->data.a == 1)
		global->data.a = 0;
	if (keycode == KEY_RIGHT_VISION && global->data.right == 1)
		global->data.right = 0;
	if (keycode == KEY_LEFT_VISION && global->data.left == 1)
		global->data.left = 0;
	return (0);
}

int				key_move(t_global *global)
{
	if (global->data.w == 1)
		key_move2(global);
	if (global->data.s == 1)
		key_move3(global);
	if (global->data.d == 1)
		key_move4(global);
	if (global->data.a == 1)
		key_move5(global);
	if (global->data.right == 1)
		key_vision_right(global);
	if (global->data.left == 1)
		key_vision_left(global);
	return (0);
}
