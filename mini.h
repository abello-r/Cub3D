/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abello-r <abello-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:36 by abello-r          #+#    #+#             */
/*   Updated: 2020/12/30 12:34:49 by abello-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "./libft/libft.h"
# include "./gnl/get_next_line_bonus.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

# define KEY_UP					13
# define KEY_DOWN				1
# define KEY_RIGHT				2
# define KEY_LEFT				0
# define KEY_RIGHT_VISION		124
# define KEY_LEFT_VISION		123
# define ESCAPE					53
# define ER1 "Argumento inválido : Revisa que el archivo termine en \".cub\"."
# define ER2 "Argumento inválido : Prueba escribiendo \"--save\"."
# define ALPN "abcdefghiklmnñopqrstuvwxyx0123456789ABCDEFGHIGKLMNÑOPQRSTUVWXYZ"

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	int				up_switch;
	int				down_switch;
	int				left_switch;
	int				right_switch;
	int				color;
	int				w;
	int				s;
	int				d;
	int				a;
	int				right;
	int				left;
}					t_data;

typedef	struct		s_mapa
{
	int				i;
	int				old;
	int				xpvu;
	char			**memoria;
	char			*ruta_sprite;
	char			*ruta_norte;
	char			*ruta_sur;
	char			*ruta_este;
	char			*ruta_oeste;
	int				width;
	int				height;
	int				color_f;
	int				color_c;
	char			*tmp1;
	char			*tmp2;
	int				bmp;
	char			**copy_mem;
}					t_mapa;

typedef	struct		s_textura_norte
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_norte;
	int				tex_width;
	int				tex_height;
}					t_textura_norte;

typedef	struct		s_textura_sur
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_sur;
	int				tex_width;
	int				tex_height;
}					t_textura_sur;

typedef	struct		s_textura_este
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_este;
	int				tex_width;
	int				tex_height;
}					t_textura_este;

typedef	struct		s_textura_oeste
{
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_oeste;
	int				tex_width;
	int				tex_height;
}					t_textura_oeste;

typedef struct		s_sprite
{
	double			distance;
	int				num;
	int				tmp_num;
	int				*order;
	char			*sprites;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*tex_add;
	unsigned int	*buffer;
	double			*z_buffer;
	int				tex_width;
	int				tex_height;
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				drawstart_x;
	int				drawend_x;
	int				drawstart_y;
	int				drawend_y;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
}					t_sprite;

typedef struct		s_xysp
{
	double			rel;
	double			x;
	double			y;
}					t_xysp;

typedef struct		s_player
{
	char			nswe;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			old_dir_x;
	double			old_plane_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perpwalldist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			move_speed;
	double			rot_speed;
	int				tex_width;
	int				tex_height;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			step;
	double			tex_pos;
	void			*textura;
	unsigned int	*buffer;

}					t_player;

typedef struct		s_arg
{
	int				r;
	int				n;
	int				so;
	int				w;
	int				e;
	int				s;
	int				f;
	int				c;
	int				map;

}					t_arg;

typedef	struct		s_global
{
	t_data			data;
	t_player		player;
	t_textura_norte	textura_norte;
	t_textura_sur	textura_sur;
	t_textura_este	textura_este;
	t_textura_oeste	textura_oeste;
	t_mapa			mapa;
	t_sprite		sprite;
	t_xysp			*xysp;
	t_arg			arg;
}					t_global;

void				my_mlx_pixel_put(t_global *global, int x, int y, int color);
int					key_move(t_global *global);
void				ft_get_texture(t_global *global);
void				ft_fill_texture(t_global *global);
void				ft_init_structs(t_global *global);
void				ft_init_structs2(t_global *global);
int					ft_control_error(t_global *global, int argc, char **argv);
void				ft_print_error(char *s);
int					ft_parseo(t_global *global, char **argv);
int					ft_check_lines(t_global *global, char *line);
int					ft_check_resolucion(t_global *global, int x);
int					ft_is_space(char *line);
int					ft_check_ruta_norte(t_global *global, char *line);
int					ft_check_ruta_sur(t_global *global, char *line);
int					ft_check_ruta_este(t_global *global, char *line);
int					ft_check_ruta_oeste(t_global *global, char *line);
int					ft_check_ruta_sprite(t_global *global, char *line);
void				ft_check_color_f(t_global *global, char *line);
void				ft_check_color_c(t_global *global, char *line);
int					ft_rgb (int r, int g, int b);
void				ft_check_map(t_global *global, char *line);
void				ft_reservar_map(t_global *global);
void				ft_fill_map(t_global *global, char **argv);
void				ft_check_memoria(t_global *global);
void				ft_check_memoria2(t_global *global);
void				ft_flood_fill(t_global *global, int x, int y);
char				**ft_cpy_memory(t_global *global, char **mem);
void				ft_nswe(t_global *global);
void				ft_nswe_complemento(t_global *global);
void				ft_free_var(char **color, char *tmp);
void				ft_res_sprites(t_global *global);
void				ft_sort_sprites(t_global *global);
void				ft_sort_sprites2(t_global *global);
void				ft_ray_sprite(t_global *global);
void				ft_ray_sprite2(t_global *global, int i);
void				ft_ray_sprite3(t_global *global);
void				ft_ray_sprite4(t_global *global, int d, int y);
int					raycasting(t_global *global);
void				raycasting2(t_global *global, int x, int w);
void				raycasting3(t_global *global);
void				raycasting4(t_global *global);
void				raycasting5(t_global *global);
void				raycasting6(t_global *global);
void				raycasting7(t_global *global, int x, int y);
int					ft_screenshot(t_global *global);
void				ft_bit_rgb(unsigned char *s, int i);
void				ft_bmp_cabezera(t_global *global, int fd, int ps);
void				ft_free_matriz(t_global *global);
int					ft_exit(t_global *global);
void				ft_no_repeat(t_global *global);
void				key_move2(t_global *global);
void				key_move3(t_global *global);
void				key_move4(t_global *global);
void				key_move5(t_global *global);
void				key_vision_right(t_global *global);
void				key_vision_left(t_global *global);
void				ft_get_texture2(t_global *global);
void				ft_check_lines2(t_global *global, char *line, int i);
int					key_press(int keycode, t_global *global);
int					key_release(int keycode, t_global *global);
#endif
