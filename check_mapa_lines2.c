/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:13:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/22 19:39:03 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_nswe_complemento(t_global *global)
{
	if (global->player.nswe == 'W')
	{
		global->player.dirX = 0.0;
		global->player.dirY = -1;
		global->player.planeX = -0.66;
		global->player.planeY = 0.0;
	}
	else if (global->player.nswe == 'E')
	{
		global->player.dirX = 0.0;
		global->player.dirY = 1;
		global->player.planeX = 0.66;
		global->player.planeY = 0.0;
	}
}

void		ft_check_memoria(t_global *global) // Primera leída 
{
	char	**copy_mem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < global->mapa.xpvu)
	{
		j = 0;
		while (j < global->mapa.old)
		{
			if (global->mapa.memoria[i][j] == '2')
				global->sprite.num++;
			if (!(ft_strchr(" 012NESW", global->mapa.memoria[i][j])))
				ft_print_error("Carácter inválido en el mapa");
			if (ft_strchr("NESW", global->mapa.memoria[i][j]))
			{
				global->player.nswe = global->mapa.memoria[i][j];
				global->mapa.memoria[i][j] = '0';
				if (global->player.posX > 0 || global->player.posY < 0)
					ft_print_error("Hay más de un jugador en el mapa");
				global->player.posY = j + 0.5;
				global->player.posX = i + 0.5;
			}
			if (global->mapa.memoria[i][j] == ' ')
				global->mapa.memoria[i][j] = '0';
			j++;
		}
		i++;
	}
	global->sprite.tmp_num = global->sprite.num;
	if (global->player.posX == 0 || global->player.posY == 0)
		ft_print_error("No hay jugador");
	copy_mem = ft_cpy_memory(global, global->mapa.memoria);
	ft_res_sprites(global);
	ft_flood_fill(global, (int)global->player.posX, (int)global->player.posY);
	global->mapa.memoria = ft_cpy_memory(global, copy_mem);
	ft_free_matriz(global, copy_mem);
	ft_nswe(global);
	
}

void		ft_fill_map(t_global *global, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	int		j;
	int		w;

	fd = open(argv[1], O_RDONLY);
	i = 0;
	j = 0;
	w = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		j = 0;
		while (line[j] == ' ')
		{
			line[j] = '0';
			j++;
		}
		if (line[j] == '0' || line[j] == '1' || line[j] == '2')
			ft_strlcpy(global->mapa.memoria[w++], line, ft_strlen(line) + 1);
		free(line);
		line = NULL;
	}
	j = 0;
	while (line[j] == ' ')
	{
		line[j] = '0';
		j++;
	}
	if (line[j] != '\0')
		ft_strlcpy(global->mapa.memoria[w++], line, ft_strlen(line) + 1);
	free(line);
	line = NULL;
	close(fd);
	ft_check_memoria(global);
}

void		ft_free_matriz(t_global *global, char **matriz)
{
	int i;

	i = 0;
	while (i < global->mapa.xpvu)
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}