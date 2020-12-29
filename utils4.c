/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:57:24 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 20:48:44 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			ft_init_structs(t_global *global)
{
	global->player.dir_x = -1;
	global->player.dir_y = 0;
	global->player.plane_x = 0;
	global->player.plane_y = 0.66;
	global->player.move_speed = 0.16;
	global->player.rot_speed = 0.09;
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

void			ft_init_structs2(t_global *global)
{
	global->arg.r = 0;
	global->arg.n = 0;
	global->arg.so = 0;
	global->arg.w = 0;
	global->arg.e = 0;
	global->arg.s = 0;
	global->arg.f = 0;
	global->arg.c = 0;
	global->arg.map = 0;
}

void			ft_print_error(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	exit(0);
}

int				ft_is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

void			my_mlx_pixel_put(t_global *global, int x, int y, int color)
{
	char *dst;

	dst = (char *)global->data.addr +
	(y * global->data.line_lenght + x * (global->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
