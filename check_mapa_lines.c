/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:20:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/17 14:30:12 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_check_map(t_global *global, char *line)
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
	if(!(global->mapa.memoria = malloc( sizeof(char*) * global->mapa.xpvu)))
		ft_print_error("No hay espacio para guardar el mapa");
	while (i < global->mapa.xpvu)
	{	
		j = 0;
		if(!(global->mapa.memoria[i] = malloc(sizeof(char) * global->mapa.old)))
			ft_print_error("No hay espacio para guardar el mapa");
		while (j < global->mapa.old)
		{
			global->mapa.memoria[i][j] = '0';
			j++;
		}	
		i++;
	}
}

void ft_fill_map(t_global *global, char **argv)
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
	while((i = get_next_line(fd, &line)) > 0)
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

void ft_check_memoria (t_global *global)
{
	char **copy_mem;
	int i;
	int j;

	i = 0;
	j =  0;
	while (i < global->mapa.xpvu)
	{
		j = 0;
		while(j < global->mapa.old)
		{
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
	copy_mem = ft_cpy_memory(global, global->mapa.memoria);
	ft_flood_fill(global, (int)global->player.posX, (int)global->player.posY);
	global->mapa.memoria = ft_cpy_memory(global, copy_mem);
	ft_nswe(global);
	int		t;
	int		r;

	t = 0;
	r = 0;
	while (t < global->mapa.xpvu)
	{
		r = 0;
		while (r < global->mapa.old)
		{
			printf("%c", global->mapa.memoria[t][r]);
			r++;
		}
		printf("\n");
		t++;
	}
}

void	ft_flood_fill(t_global *global, int x, int y)	
{
	if (x < 0 || x >= global->mapa.xpvu || y < 0 || y >= global->mapa.old)
		ft_print_error("Mapa abierto");

	if ((ft_strchr(" 0N2ESW", global->mapa.memoria[x][y])))
	{
		global->mapa.memoria[x][y] = '*';
		ft_flood_fill(global, x + 1, y);
		ft_flood_fill(global, x, y + 1);
		ft_flood_fill(global, x - 1, y);
		ft_flood_fill(global, x, y - 1);
	}
}

char **ft_cpy_memory(t_global *global, char **mem)
{
	char **copy;
	int i;

	if(!(copy = malloc(sizeof(char*) * global->mapa.xpvu)))
		ft_print_error("No hay espacio para guardar el mapa");
	i = 0;
	while (i < global->mapa.xpvu)
	{
		copy[i] = ft_strdup(mem[i]);
		i++;
	}
	return(copy);
}

void	ft_nswe(t_global *global)
{
	if (global->player.nswe == 'N')
	{
		global->player.dirX = -1;
		global->player.dirY = 0.0;
		global->player.planeX = 0.0;
		global->player.planeY = 0.66;
	}
	else if (global->player.nswe == 'S')
	{
		global->player.dirX = 1;
		global->player.dirY = 0.0;
		global->player.planeX = 0.0;
		global->player.planeY = -0.66;
	}
	else if (global->player.nswe == 'W')
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