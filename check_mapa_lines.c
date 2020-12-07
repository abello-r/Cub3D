/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapa_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:20:12 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/07 14:34:32 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_check_map(t_global *global, char *line)
{

/*----------------CONTROL DE LONGITUD LINEAL---------------*/
	char	*memoria;
	int		x;
	int		size;

	x = ft_strlen(line);
	global->mapa.old = global->mapa.old == 0 ? x : global->mapa.old;
	if (global->mapa.old < x)
		global->mapa.old = x;

/*----------------CONTROL DE DIMENSIONES---------------*/
	global->mapa.xpvu = global->mapa.xpvu == 0 ? 1 : global->mapa.xpvu;
	if (global->mapa.xpvu > 0)
		global->mapa.xpvu++;
	size = global->mapa.old * (global->mapa.xpvu - 1);

/*----------------ALOCAR MEMORIA POR TAMAÑO---------------*/
	x = 0;
	if (!(memoria = malloc(1 * size)))
		ft_print_error("No se pudo almacenar memoria para el mapa");
	while(memoria[x] != '\0')
	{
		memoria[x] = '0';
		x++;
	}
	printf("->Memoria[%s]\n", memoria);
	printf("->Line[%s]\n", line);
	/*printf("%s", line);
	printf("\n--->[LONG = %d]<---\n", global->mapa.old);
	printf("\n--->[XPVU = %d]<---\n", global->mapa.xpvu);
	printf("--->[SIZE = %d]<---", size);*/
}