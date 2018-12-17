/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:27:15 by marvin            #+#    #+#             */
/*   Updated: 2018/12/17 19:24:03 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>

# define THREADS_NB 10
# define OFFSCREEN_RES_FACTOR (4 * 2)
typedef long double
		t_floating;

# ifdef __APPLE__
#  define MOUSE_ZOOM_IN 5
#  define MOUSE_ZOOM_OUT 4
#  define K_UP 126
#  define K_DWN 125
#  define K_LFT 123
#  define K_RGT 124
#  define K_W 13
#  define K_S 1
#  define K_PLS 69
#  define K_MNS 78
#  define K_R 15
#  define K_ESC 53
# elif __linux__
#  define MOUSE_ZOOM_IN 5
#  define MOUSE_ZOOM_OUT 4
#  define K_UP 65362
#  define K_DWN 65364
#  define K_LFT 65361
#  define K_RGT 65363
#  define K_W 119
#  define K_S 115
#  define K_PLS 61
#  define K_MNS 45
#  define K_R 114
#  define K_ESC 65307
# endif


typedef struct	s_img t_img;
typedef struct	s_mlx t_mlx;
typedef struct	s_pixel t_pixel;
typedef struct	s_complex t_complex;
typedef struct	s_complex t_c;
typedef struct	s_res t_res;
typedef struct	s_thread t_thread;
typedef struct	s_env t_env;

typedef struct	s_img
{
	void		*ptr;
	int			*px;
	int			line_s;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct	s_pixel
{
	int			re_x;
	int			im_y;
}				t_pixel;

typedef struct	s_complex
{
	t_floating		re;
	t_floating		im;
}				t_complex;

typedef struct	s_res
{
	int			w;
	int			h;
}				t_res;


typedef struct	s_thread
{
	pthread_t	thread;
	t_env		*env;
	int			line_start;
	int			line_end;
}				t_thread;

typedef struct	s_env
{
	t_mlx		*mlx;
	t_res		res;
	void		*(*fract)(void*);
	t_complex	c;
	t_complex	z_step;
	int			iter_max;
	t_floating	zoom;
	t_complex	pos;
	t_complex	mouse;
	t_thread	threads[THREADS_NB];
}				t_env;

/*
**	Error handling
*/
void			chaos(void *fate);
void			msg_exit(char *msg, void *data);

/*
**	rendering
*/
void			render(t_mlx *mlx, t_env *data);
void			render_offscreen(t_env *data);
void			launch_threads(t_env *data);
void			export_bmp(t_env *data);

int				red_col(int iter);
int				blu_col(int iter);

void			*draw_mandel(void *thread_data);
void			*draw_julia(void *thread_data);
void			*draw_slow_mandel(void *thread_data);
void			*draw_slow_julia(void *thread_data);
void			*draw_burningship(void *thread_data);
void			*draw_cos_mandel(void *thread_data);

/*
**	Operations on t_complex type
*/
void			c_fill_complex(t_complex *c, float re, float im);
double			c_squared_modulus(t_complex *z);
int				c_squared_mod_inf(t_complex *z, double threshhold);
t_complex		*c_sum(t_complex *z, t_complex *add);
t_complex		*c_mult(t_complex *z, t_complex *mult);
t_complex		*c_square(t_complex *z);
t_complex		*c_cos(t_complex *c);
t_complex		*c_sin(t_complex *c);
t_complex		*c_div(t_complex *c, t_complex *divi);
t_complex		*c_sub(t_complex *z, t_complex *sub);
t_complex		*c_opsite(t_complex *c);
t_complex		*c_swap(t_complex *c1, t_complex *c2);
t_complex		*c_abs(t_complex *c);

/*
**	Mlx hooks
*/
int				mouse_pos(int x, int y, void *param);
int				mouse_click(int x, int y, int keycode, void *param);
int				keypress(int keycode, void *param);

void			print_instructions(void);

#endif
