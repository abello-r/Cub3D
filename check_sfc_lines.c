/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sfc_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:26 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/03 12:14:17 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int			ft_check_ruta_sprite(t_global *global, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "S ", 2) == 0)
		x = x + 2;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	global->mapa.ruta_sprite = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	return (0);
}

void		ft_check_color_f(t_global *global, char *line)
{
	char	colorhx[20];
	char	*tmp;
	int		x;
	int		i;

	x = 1;
	i = 0;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	if (ft_strncmp((tmp + x), "F ", 2) == 0)
		x = x + 2;
	while (tmp[x] != '\0')
	{
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			ft_print_error(("Hay un carácter inválido en la línea \"F\""));
		else if (ft_isdigit(tmp[x]))
			colorhx[i++] = tmp[x];
		x++;
	}
	colorhx[i] = '\0';
	free(tmp);
	tmp = NULL;
	global->mapa.color_f = ft_atoi(colorhx);
	global->mapa.color_f > 255255255 ? ft_print_error("Max (255,255,255)") : 0;
}

void		ft_check_color_c(t_global *global, char *line)
{
	char	colorhx[20];
	char	*tmp;
	int		x;
	int		i;

	x = 1;
	i = 0;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	if (ft_strncmp((tmp + x), "C ", 2) == 0)
		x = x + 2;
	while (tmp[x] != '\0')
	{
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			ft_print_error(("Hay un carácter inválido en la línea \"C\""));
		else if (ft_isdigit(tmp[x]))
			colorhx[i++] = tmp[x];
		x++;
	}
	colorhx[i] = '\0';
	free(tmp);
	tmp = NULL;
	global->mapa.color_c = ft_atoi(colorhx);
	global->mapa.color_f > 255255255 ? ft_print_error("Max (255,255,255)") : 0;
}
