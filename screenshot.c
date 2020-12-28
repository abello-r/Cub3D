/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:26:28 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/28 15:09:50 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			ft_bit_rgb(unsigned char *s, int i)
{
	s[0] = (unsigned char)i;
	s[1] = (unsigned char)(i >> 8);
	s[2] = (unsigned char)(i >> 16);
	s[3] = (unsigned char)(i >> 24);
}

void			ft_bmp_cabezera(t_global *global, int fd, int ps)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (global->mapa.width * 3 * global->mapa.height) +
		(ps * global->mapa.width);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	ft_bit_rgb(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	ft_bit_rgb(header + 18, global->mapa.width);
	ft_bit_rgb(header + 22, -global->mapa.height);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
	write(fd, global->data.addr, global->mapa.width * global->mapa.height * 4);
}

int				ft_screenshot(t_global *global)
{
	int	fd;
	int	padsize;

	padsize = (4 - (global->mapa.width * 3) % 4) % 4;
	write(1, "\n\x1b[32m[Captura hecha con éxito]\n\n\x1b[0m", 39);
	if (!(fd = open("./cub3D.bmp", O_WRONLY | O_CREAT, S_IRWXU |
	O_TRUNC | O_APPEND)))
		ft_print_error("No se puede crear el BMP\x1b[0m");
	ft_bmp_cabezera(global, fd, padsize);
	close(fd);
	exit(0);
	return (1);
}
