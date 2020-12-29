/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:13:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 17:05:50 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_nswe_complemento(t_global *global)
{
	if (global->player.nswe == 'W')
	{
		global->player.dir_x = 0.0;
		global->player.dir_y = -1;
		global->player.plane_x = -0.66;
		global->player.plane_y = 0.0;
	}
	else if (global->player.nswe == 'E')
	{
		global->player.dir_x = 0.0;
		global->player.dir_y = 1;
		global->player.plane_x = 0.66;
		global->player.plane_y = 0.0;
	}
}

void		ft_fill_map(t_global *global, char **argv)
{
	char	*line;
	int		fd;
	int		j;
	int		w;

	fd = open(argv[1], O_RDONLY);
	w = 0;
	while (get_next_line(fd, &line) > 0 && (j = -1))
	{
		while (line[++j] == ' ')
			line[j] = '0';
		if (line[j] == '0' || line[j] == '1' || line[j] == '2')
			ft_strlcpy(global->mapa.memoria[w++], line, ft_strlen(line) + 1);
		free(line);
		line = NULL;
	}
	j = -1;
	while (line[++j] == ' ')
		line[j] = '0';
	if (line[j] != '\0')
		ft_strlcpy(global->mapa.memoria[w++], line, ft_strlen(line) + 1);
	free(line);
	close(fd);
	ft_check_memoria(global);
}

void		ft_check_memoria(t_global *global)
{
	int		i;
	int		j;

	i = -1;
	while (++i < global->mapa.xpvu && (j = -1))
		while (++j < global->mapa.old)
		{
			global->mapa.memoria[i][j] == '2' ? global->sprite.num++ : 0;
			if (!(ft_strchr(" 012NESW", global->mapa.memoria[i][j])))
				ft_print_error("Carácter inválido en el mapa");
			if (ft_strchr("NESW", global->mapa.memoria[i][j]))
			{
				global->player.nswe = global->mapa.memoria[i][j];
				global->mapa.memoria[i][j] = '0';
				if (global->player.pos_x > 0 || global->player.pos_y < 0)
					ft_print_error("Hay más de un jugador en el mapa");
				global->player.pos_y = j + 0.5;
				global->player.pos_x = i + 0.5;
			}
			if (global->mapa.memoria[i][j] == ' ')
				global->mapa.memoria[i][j] = '0';
		}
	ft_check_memoria2(global);
}

void		ft_check_memoria2(t_global *global)
{
	int i;

	if (global->player.pos_x == 0 || global->player.pos_y == 0)
		ft_print_error("No hay jugador");
	global->sprite.tmp_num = global->sprite.num;
	global->mapa.copy_mem = ft_cpy_memory(global, global->mapa.memoria);
	ft_res_sprites(global);
	ft_flood_fill(global, (int)global->player.pos_x, (int)global->player.pos_y);
	i = 0;
	while (i < global->mapa.xpvu)
	{
		free(global->mapa.memoria[i]);
		global->mapa.memoria[i] = NULL;
		i++;
	}
	free(global->mapa.memoria);
	global->mapa.memoria = ft_cpy_memory(global, global->mapa.copy_mem);
	ft_free_matriz(global);
	ft_nswe(global);
}

void		ft_free_matriz(t_global *global)
{
	int i;

	i = 0;
	while (i < global->mapa.xpvu)
	{
		free(global->mapa.copy_mem[i]);
		global->mapa.copy_mem[i] = NULL;
		i++;
	}
	free(global->mapa.copy_mem);
}
