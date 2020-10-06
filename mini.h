/*----------------------------------------------------*/

#ifndef MINI_H
# define MINI_H

/*----------------------------------------------------*/

# include "./libft/libft.h"
# include <mlx.h>
# include <math.h>

# define KEY_UP				126
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_LEFT			123

/*----------------------------------------------------*/

typedef struct	s_data // Pantalla e imagén.
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

}				t_data;

/*----------------------------------------------------*/

typedef struct	s_player // Datos de Jugador
{
	int		*N; // Jugador

	double	posX; // Posición inicial en x.
	double	posY; // Posición inicial en y.

	double	dirX; // Vector de dirección inicial en x.
	double	dirY; // Vector de dirección inicial en y.

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

	double	perpWallDist;
	double	time; // Tiempo del fps actual.
	double	old_time;	// Tiempo previo del fps.


}				t_player;

/*----------------------------------------------------*/

typedef	struct	s_global // Conjunto de estructuras.
{
	t_data		data; // Datos de imagen y teclas.
	t_player	player; // Datos del jugador.

}				t_global;

/*----------------------------------------------------*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color); // Función auxiliar para imprimir pixeles.

#endif