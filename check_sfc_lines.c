/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sfc_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:26 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/28 18:02:44 by abello-r         ###   ########.fr       */
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
	global->arg.s++;
	return (0);
}

void		ft_check_color_f(t_global *global, char *line)
{
	int		x;
	int		c;
	char	*tmp;
	char	**color;

	x = 1;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	x += ft_strncmp((tmp + x), "F ", 2) == 0 ? 2 : 0;
	color = ft_split(&tmp[x], ',');
	if (color[0] == '\0' || color[1] == '\0' || color[2] == '\0')
		ft_print_error("Falta un número en el suelo");
	c = ft_rgb(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	while (tmp[x] != '\0')
	{
		if (tmp[x] == ',' && tmp[x + 1] == ',')
			ft_print_error("Sólo 1 coma para separar");
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			ft_print_error(("Hay un carácter inválido en la línea \"F\""));
		x++;
	}
	ft_free_var(color, tmp);
	free(color);
	global->mapa.color_f = c + !(++global->arg.f);
}

void		ft_check_color_c(t_global *global, char *line)
{
	int		x;
	int		c;
	char	*tmp;
	char	**color;

	x = 1;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	x += ft_strncmp((tmp + x), "C ", 2) == 0 ? 2 : 0;
	color = ft_split(&tmp[x], ',');
	if (color[0] == '\0' || color[1] == '\0' || color[2] == '\0')
		ft_print_error("Falta un número en el cielo");
	c = ft_rgb(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	while (tmp[x] != '\0')
	{
		if (tmp[x] == ',' && tmp[x + 1] == ',')
			ft_print_error("Sólo 1 coma para separar");
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			ft_print_error(("Hay un carácter inválido en la línea \"C\""));
		x++;
	}
	ft_free_var(color, tmp);
	free(color);
	global->mapa.color_c = c + !(++global->arg.c);
}

int			ft_rgb(int r, int g, int b)
{
	int rgb;

	if (r > 255 || g > 255 || b > 255)
		ft_print_error("El RGB máximo es de 255");
	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void		ft_free_var(char **color, char *tmp)
{
	int i;

	i = 0;
	while (color[i])
	{
		free(color[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}
