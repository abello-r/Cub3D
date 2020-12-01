/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sfc_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:26 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/01 14:18:00 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		ft_check_ruta_sprite(t_global *global, char *line)
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

