/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:20:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 17:05:51 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_check_map(t_global *global, char *line)
{
	int		x;

	x = ft_strlen(line);
	global->mapa.old = global->mapa.old == 0 ? x : global->mapa.old;
	if (global->mapa.old < x)
		global->mapa.old = x;
	global->mapa.xpvu++;
}

void		ft_reservar_map(t_global *global)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	global->mapa.old == 0 ? ft_print_error("No existe el mapa") : 0;
	global->mapa.xpvu == 0 ? ft_print_error("No existe el mapa") : 0;
	if (!(global->mapa.memoria = malloc(sizeof(char*) * global->mapa.xpvu)))
		ft_print_error("No hay espacio para guardar el mapa");
	while (i < global->mapa.xpvu)
	{
		j = 0;
		if (!(global->mapa.memoria[i] = malloc(sizeof(char)
			* global->mapa.old)))
			ft_print_error("No hay espacio para guardar el mapa");
		while (j < global->mapa.old)
		{
			global->mapa.memoria[i][j] = '0';
			j++;
		}
		i++;
	}
}

void		ft_flood_fill(t_global *global, int x, int y)
{
	if (x < 0 || x >= global->mapa.xpvu || y < 0 || y >= global->mapa.old)
		ft_print_error("Mapa abierto");
	if ((ft_strchr(" 0N2ESW", global->mapa.memoria[x][y])))
	{
		if (global->mapa.memoria[x][y] == '2')
		{
			--global->sprite.tmp_num;
			global->xysp[global->sprite.tmp_num].x = x + 0.5;
			global->xysp[global->sprite.tmp_num].y = y + 0.5;
		}
		global->mapa.memoria[x][y] = '*';
		ft_flood_fill(global, x + 1, y);
		ft_flood_fill(global, x, y + 1);
		ft_flood_fill(global, x - 1, y);
		ft_flood_fill(global, x, y - 1);
	}
}

char		**ft_cpy_memory(t_global *global, char **mem)
{
	char	**copy;
	int		i;

	if (!(copy = malloc(sizeof(char*) * global->mapa.xpvu)))
		ft_print_error("No hay espacio para guardar el mapa");
	i = 0;
	while (i < global->mapa.xpvu)
	{
		copy[i] = ft_strdup(mem[i]);
		i++;
	}
	return (copy);
}

void		ft_nswe(t_global *global)
{
	if (global->player.nswe == 'N')
	{
		global->player.dir_x = -1;
		global->player.dir_y = 0.0;
		global->player.plane_x = 0.0;
		global->player.plane_y = 0.66;
	}
	else if (global->player.nswe == 'S')
	{
		global->player.dir_x = 1;
		global->player.dir_y = 0.0;
		global->player.plane_x = 0.0;
		global->player.plane_y = -0.66;
	}
	else if (global->player.nswe == 'W')
		ft_nswe_complemento(global);
	else if (global->player.nswe == 'E')
		ft_nswe_complemento(global);
}
