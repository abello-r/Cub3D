/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:26:28 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/22 13:50:36 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_screenshot(t_global *global)
{
	int fd;

	raycasting(global);
	fd = open("./screenshot.txt", O_WRONLY | O_CREAT | S_IRWXU | O_TRUNC | O_APPEND);
	write(fd, "hola gueva", 11);
	//global->data.img = mlx_get_data_addr()
}
void ft_bit_rgb(unsigned char *s, int i)
{
	s[0] = (unsigned char) i;
	s[1] = (unsigned char) (i >> 8);
	s[2] = (unsigned char) (i >> 16);
	s[3] = (unsigned char) (i >> 24);
}