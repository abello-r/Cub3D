/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:16 by abello-r          #+#    #+#             */
/*   Updated: 2021/01/04 13:00:42 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int				ft_control_error(t_global *global, int argc, char **argv)
{
	char	*tmp;

	argc < 2 || argc > 3 ? ft_print_error("Número de argumentos inválido.") : 0;
	if (argc == 2 || argc == 3)
	{
		if ((tmp = ft_strchr(argv[1], '.')) == NULL)
			ft_print_error(ER1);
		if ((ft_strncmp(tmp, ".cub\0", 5)) != 0)
			ft_print_error(ER1);
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save\0", 7) != 0)
				ft_print_error(ER2);
			else
			{
				raycasting(global);
				ft_screenshot(global);
			}
		}
	}
	return (0);
}

int				ft_parseo(t_global *global, char **argv)
{
	char	*line;
	int		fd;
	int		x;

	x = 0;
	line = NULL;
	global->mapa.i = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_print_error("El archivo \".cub\" que intentas abrir no existe.");
	while ((global->mapa.i = get_next_line(fd, &line)) > 0)
	{
		ft_check_lines(global, line);
		free(line);
		line = NULL;
		x++;
	}
	ft_check_lines(global, line);
	ft_no_repeat(global);
	close(fd);
	free(line);
	line = NULL;
	ft_reservar_map(global);
	ft_fill_map(global, argv);
	return (0);
}

int				ft_check_lines(t_global *global, char *line)
{
	int i;
	int x;

	x = 1;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (global->mapa.xpvu > 0 || global->mapa.old > 0)
	{
		if (line[i] == ' ' || line[i] == '0' ||
				line[i] == '1' || line[i] == '2')
			ft_check_map(global, line);
		else if (line[i] == '\0' || ft_isascii(line[i]))
			ft_print_error("Mapa inválido por saltos de linea o carácter");
	}
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		global->mapa.tmp1 = line;
		ft_check_resolucion(global, x);
	}
	else if (line[i] == 'N' && line[i + 1] == 'O')
		ft_check_ruta_norte(global, line);
	else
		ft_check_lines2(global, line, i);
	return (0);
}
