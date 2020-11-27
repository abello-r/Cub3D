#include "mini.h"

int		ft_check_resolucion(t_global *global, int x)  // Esta función revisa la linea de resolución.
{
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
	else if (global->mapa.width > 5120 || global->mapa.height > 2880)
	{
		global->mapa.width = 5120;
		global->mapa.height = 2880;
	}
	while (ft_is_space(&global->mapa.tmp1[x]))
		x++;
	if (global->mapa.tmp1[x] != '\0')
		ft_print_error("Hay un carácter inválido en la resolución.");
	return (0);
}

int		ft_check_ruta(t_global *global, int x, char **line)
{
	global->mapa.tmp2 = *line;
	x++;
	if(global->mapa.tmp2[x] != 'O')
		ft_print_error("La linea de textura \"NO\" es inválida.");
	x++;


	return (0);
}