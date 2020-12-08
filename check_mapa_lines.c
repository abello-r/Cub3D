/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:20:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/08 13:42:33 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_check_map(t_global *global, char *line)
{
/*----------------CONTROL DE LONGITUD LINEAL---------------*/
	int		x;

	x = ft_strlen(line);
	global->mapa.old = global->mapa.old == 0 ? x : global->mapa.old;
	if (global->mapa.old < x)
		global->mapa.old = x;

/*----------------CONTROL DE DIMENSIONES---------------*/
	global->mapa.xpvu++;
}

void		ft_fill_map(t_global *global, char **argv)
{
	int fd;
	int i = 0;
	int x = 0;
	char *line;
	char **memoria;

	if(!(memoria = ft_calloc(global->mapa.xpvu, sizeof(char*))))
		ft_print_error("No hay espacio para guardar el mapa");
	while (global->mapa.xpvu > x)
	{	
		memoria[x] = ft_calloc(global->mapa.old, sizeof(char));

		printf("[%s]", memoria[x]);
		x++;
	}
	fd = open(argv[1], O_RDONLY);
	while((i = get_next_line(fd, &line)) > 0)
	{
		free(line);
		line = NULL;
	}
	close(fd);

}