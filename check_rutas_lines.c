/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rutas_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:26 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/28 15:54:31 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		ft_check_resolucion(t_global *global, int x)
{
	while (ft_is_space(&global->mapa.tmp1[x]))
		x++;
	x += global->mapa.tmp1[x] == 'R';
	while (ft_is_space(&global->mapa.tmp1[x]))
		x++;
	if (!ft_isdigit(global->mapa.tmp1[x]))
		ft_print_error("Has introducido una resolución inválida.");
	global->mapa.width = ft_atoi(&global->mapa.tmp1[x]);
	while (ft_isdigit(global->mapa.tmp1[x]))
		x++;
	while (ft_is_space(&global->mapa.tmp1[x]))
		x++;
	global->mapa.height = ft_atoi(&global->mapa.tmp1[x]);
	while (ft_isdigit(global->mapa.tmp1[x]))
		x++;
	if (global->mapa.width < 1 || global->mapa.height < 1)
		ft_print_error("La resolucíon miníma es \"1x1\", prueba a cambiarla.");
	global->mapa.width = global->mapa.width > 2560 ? 2560 : global->mapa.width;
	global->mapa.height = global->mapa.height > 1440 ?
							1440 : global->mapa.height;
	while (ft_is_space(&global->mapa.tmp1[x]))
		x++;
	if (global->mapa.tmp1[x] != '\0')
		ft_print_error("Hay un carácter inválido en la resolución.");
	return (!++global->arg.r);
}

int		ft_check_ruta_norte(t_global *global, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "NO ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	global->mapa.ruta_norte = ft_strtrim(tmp, " ");
	free(tmp);
	global->arg.n++;
	return (0);
}

int		ft_check_ruta_sur(t_global *global, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "SO ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	global->mapa.ruta_sur = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	global->arg.so++;
	return (0);
}

int		ft_check_ruta_este(t_global *global, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "WE ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	global->mapa.ruta_este = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	global->arg.e++;
	return (0);
}

int		ft_check_ruta_oeste(t_global *global, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "EA ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	global->mapa.ruta_oeste = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	global->arg.w++;
	return (0);
}
