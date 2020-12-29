/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:00:03 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/29 16:57:31 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void			ft_get_texture(t_global *global)
{
	if (global->player.side == 0 && global->player.step_x == -1)
	{
		global->player.tex_width = global->textura_norte.tex_width;
		global->player.tex_height = global->textura_norte.tex_height;
		global->player.textura = global->textura_norte.tex_norte;
		global->player.buffer = (unsigned int *)
		mlx_get_data_addr(global->player.textura,
		&global->textura_norte.bits_per_pixel,
		&global->textura_norte.line_lenght, &global->textura_norte.endian);
	}
	if (global->player.side == 0 && global->player.step_x == 1)
	{
		global->player.tex_width = global->textura_sur.tex_width;
		global->player.tex_height = global->textura_sur.tex_height;
		global->player.textura = global->textura_sur.tex_sur;
		global->player.buffer = (unsigned int *)
		mlx_get_data_addr(global->player.textura,
		&global->textura_sur.bits_per_pixel,
		&global->textura_sur.line_lenght, &global->textura_sur.endian);
	}
	ft_get_texture2(global);
}

void			ft_fill_texture(t_global *global)
{
	if (!(global->textura_norte.tex_norte =
	mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_norte,
	&global->textura_norte.tex_width, &global->textura_norte.tex_height)))
		ft_print_error("La textura NORTE que has introducido no existe.");
	else if (!(global->textura_sur.tex_sur =
	mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_sur,
	&global->textura_sur.tex_width, &global->textura_sur.tex_height)))
		ft_print_error("La textura SUR que has introducido no existe.");
	else if (!(global->textura_oeste.tex_oeste =
	mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_este,
	&global->textura_oeste.tex_width, &global->textura_oeste.tex_height)))
		ft_print_error("La textura OESTE que has introducido no existe.");
	else if (!(global->textura_este.tex_este =
	mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_oeste,
	&global->textura_este.tex_width, &global->textura_este.tex_height)))
		ft_print_error("La textura ESTE que has introducido no existe.");
	if (!(global->sprite.tex_add =
	mlx_xpm_file_to_image(global->data.mlx, global->mapa.ruta_sprite,
	&global->sprite.tex_width, &global->sprite.tex_height)))
		ft_print_error("La textura del SPRITE no existe");
}
