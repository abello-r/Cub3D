/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:20:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/14 14:48:24 by abello-r         ###   ########.fr       */
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
	/*int x = 0;
	int k = 0;
	while (x < global->mapa.xpvu)
	{
		k = 0;
		while (k < global->mapa.old)
		{
			printf("%c", global->mapa.memoria[x][k]);
			k++;
		}
		printf("\n");
		x++;
	}*/
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
		if (line[j] == '1')	
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
	ft_strlcpy(global->mapa.memoria[w++], line, ft_strlen(line) + 1);
	free(line);
	line = NULL;
	close(fd);
	printf("\n");

	/*int		t;
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
	}*/
	ft_check_memoria(global);
}

void ft_check_memoria (t_global *global)
{
	int i;
	int j;

	i = 0;
	j =  0;
	while (i < global->mapa.xpvu)
	{
		j = 0;
		while(j < global->mapa.old)
		{
			if (!(ft_strchr(" 01234NESW", global->mapa.memoria[i][j])))
				ft_print_error("Carácter inválido en el mapa");
			if (global->mapa.memoria[i][j] == 'N')
			{
				global->player.posX = i + 0.5;
				global->player.posY = j - 0.5;
			}
			j++;
		}
		i++;
	}
	ft_flood_fill(global, (int)global->player.posX, (int)global->player.posY);
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

	if ((ft_strchr("0234NESW", global->mapa.memoria[x][y])))
	{
			global->mapa.memoria[x][y] = '*';

		ft_flood_fill(global, x + 1, y);
		ft_flood_fill(global, x - 1, y);
		ft_flood_fill(global, x , y + 1);
		ft_flood_fill(global, x, y - 1);	
	}
}
