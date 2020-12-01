/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:36 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/01 13:18:35 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*----------------------------------------------------*/

#ifndef MINI_H
# define MINI_H

/*----------------------------------------------------*/

# include "./libft/libft.h"
# include "./gnl/get_next_line_bonus.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define KEY_UP				13 // Arriba.
# define KEY_DOWN			1 // Abajo.
# define KEY_RIGHT			2 // Derecha.
# define KEY_LEFT			0 // Izquierda.

# define KEY_RIGHT_VISION		124 // Derecha.
# define KEY_LEFT_VISION		123 // Izquierda.

# define ESCAPE				53 // Tecla ESCAPE.

# define mapWidth			24	// Ancho del mapa.
# define mapHeight			24	// Alto del mapa.
# define num_sprites		19

/*----------------------------------------------------*/

typedef struct		s_data // Pantalla e imagén.
{
	void	*mlx;
	void	*win;
	void 	*img;
	char 	*addr;
	int 	bits_per_pixel;
	int 	line_lenght; 
	int 	endian;

	int		up_switch; // Arriba
	int		down_switch; // Abajo
	int		left_switch; // Izquierda
	int		right_switch; // Derecha
	int		color;

}				t_data;

/*---------------------------------------------------*/
typedef	struct		s_mapa // Parseo del mapa.
{
	int		i;
	
	char	*ruta_sprite;
	char	*ruta_norte;
	char	*ruta_sur;
	char	*ruta_este;
	char	*ruta_oeste;

	int		width;
	int		height;
	
	char	*tmp1;
	char	*tmp2;

	


}					t_mapa;
/*---------------------------------------------------*/

typedef	struct		s_textura_norte // Texturas NORTE
{
	int 	bits_per_pixel;
	int 	line_lenght; 
	int 	endian;
	void	*tex_norte;
}				t_textura_norte;

typedef	struct		s_textura_sur // Texturas SUR
{
	int 			bits_per_pixel;
	int 			line_lenght; 
	int 			endian;
	void			*tex_sur;
}				t_textura_sur;

typedef	struct		s_textura_este // Textura ESTE
{
	int 	bits_per_pixel;
	int 	line_lenght; 
	int 	endian;
	void	*tex_este;
}				t_textura_este;

typedef	struct		s_textura_oeste // Texturas OESTE
{
	int 	bits_per_pixel;
	int 	line_lenght; 
	int 	endian;
	void	*tex_oeste;
}				t_textura_oeste;

typedef struct		s_sprite // Sprites.
{
	int				i;
	double			x;
	double			y;
	int				textura;
	unsigned int	*z_buffer;
	char			*sprites;
}					t_sprite;

/*----------------------------------------------------*/

typedef struct		s_player // Datos de Jugador
{
	int		*N; // Jugador

	double	posX; // Posición inicial en x.
	double	posY; // Posición inicial en y.

	double	dirX; // Vector de dirección inicial en x.
	double	dirY; // Vector de dirección inicial en y.
	double	oldDirX;
	double	oldPlaneX;

	double	rayDirX; //Dirección del rayo en x.
	double	rayDirY; //Dirección del rayo en y.

	double	planeX; // Versión 2d del plano de la cámara en x.
	double	planeY; // Versión 2d del plano de la cámara en y.

	double	cameraX; // cámara.

	int		mapX; // Casilla del mapa en la que estamos ubicados eje x.
	int		mapY; // Casilla del mapa en la que estamos ubicados eje y.

	int		stepX; // Dirección en la que se dará el paso en eje x. (puede ser 1 o -1)
	int		stepY; // Dirección en la que se dará el paso en eje y. (puede ser 1 o -1)

	int		hit; // ¿Hubo un golpe en la pared? 1 = si, 0 = no.
	int		side; // Detecta que lado del mapa se golpéo (Norte/sur/este/oeste)	

	double	sideDistX; // Distancia que el rayo tiene que viajar hasta el primer lado de x.
	double	sideDistY; // Distancia que el rayo tiene que viajar hasta el primer lado de y.

	double	deltaDistX; //Distancia que el rayo tiene que viajar para ir de 1 lado x al siguiente lado x.
	double	deltaDistY; //Distancia que el rayo tiene que viajar para ir de 1 lado y al siguiente lado y.

	double	perpWallDist; // Longitud del rayo.

	int		line_height; // Altura de la linea.
	int		drawStart; // Dónde empezar a dibujar.
	int		drawEnd; // Dónde terminar.

	double	moveSpeed; // Velocidad del movimiento vectorial.
	double	rotSpeed; // Velocidad del movimiento de rotación.


	int		tex_width;
	int		tex_height;
	int		texNum;
	int		texX;
	int		texY;
	double	wallX;
	double	step;
	double	texPos;
	void	*textura;
	unsigned int *buffer;

}				t_player;

/*----------------------------------------------------*/

typedef	struct		s_global // Conjunto de estructuras.
{
	t_data			data; // Datos de imagen y teclas.
	t_player		player; // Datos del jugador.
	t_textura_norte	textura_norte; // Datos de la textura NORTE.
	t_textura_sur	textura_sur; // Datos de la textura SUR.
	t_textura_este	textura_este; // Datos de la textura ESTE.
	t_textura_oeste	textura_oeste; // Datos de la textura OESTE.
	t_sprite		sprite; // Datos de los Sprites.
	t_mapa			mapa; // Parseo del mapa.
}				t_global;

/*----------------------------------------------------*/

extern int worldMap[mapWidth][mapHeight];

void	my_mlx_pixel_put(t_data *data, int x, int y, int color); // Función auxiliar para imprimir pixeles.
int		key_move(int keycode, t_global *global); // Funcion para el movimiento del jugador y camara
void	ft_get_texture(t_global *global); // Funcion que elige que imprimir 
void	ft_fill_texture(t_global *global); // Funcion que recoge datos de las texturas
void	ft_init_structs(t_global *global); // Funcion para inicializar variables.
int		ft_control_error(int argc, char **argv); // Gestiona los errores de argumentos.
void	ft_print_error(char *s); // Muestra por pantalla los errores al ejecutar.
int		ft_parseo(t_global *global, char **argv); // Verifica que el .cub exista y lo pasa al GNL.
int		ft_check_lines(t_global *global, char *line); // Verifica las lineas.
int		ft_check_resolucion(t_global *global, int x); // Chequear la linea de resolución.
int		ft_is_space(char *line);  // Salta los espacios de las lineas en el GNL.

int		ft_check_ruta_norte(t_global *global, char *line);
int		ft_check_ruta_sur(t_global *global, char *line);
int		ft_check_ruta_este(t_global *global, char *line);
int		ft_check_ruta_oeste(t_global *global, char *line);

int		ft_check_ruta_sprite(t_global *global, char *line);
#endif