/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:27:15 by marvin            #+#    #+#             */
/*   Updated: 2018/11/26 22:27:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>		//perror() strerror()
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h> // threading !

# define THREADS_NB 8
# define INTMAX 2147483647

# ifdef __APPLE__
#  define MOUSE_ZOOM_IN 5
#  define MOUSE_ZOOM_OUT 4
#  define K_UP 126
#  define K_DWN 125
#  define K_LFT 123
#  define K_RGT 124
#  define K_Q 12
#  define K_E 14
#  define K_W 13
#  define K_S 1
#  define K_A 0
#  define K_D 2
#  define K_PLS 69
#  define K_MNS 78
#  define K_R 15
#  define K_ESC 53
# elif __linux__
#  define K_AUP 65362
#  define K_DWN 65364
#  define K_LFT 65361
#  define K_RGT 65363
#  define K_LEQ 97
#  define K_LEE 101
#  define K_LEW 119
#  define K_LES 115
#  define K_LEA 9999
#  define K_LED 9999
#  define K_PLS 69
#  define K_MNS 78
#  define K_LER 15
#  define K_ESC 65307
# endif

typedef struct	s_img
{
	void		*ptr;
	int			*data;
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
	double		re;
	double		im;
}				t_complex;

typedef struct	s_res
{
	int			w;
	int			h;
}				t_res;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_res		res;
	void		*(*fract)(void*);
	double		zoom;
	t_complex	pos;
	t_complex	mouse;
	double		thickness;
	pthread_t	threads[THREADS_NB];
}				t_data;

typedef struct	s_thrd_data
{
	t_data		*data;
	int			line_start;
	int			line_end;
	t_complex	c;
	t_complex	derr_pc;
}				t_thrd_data;

/*
**	Error handling
*/
void		chaos(void *fate);
void		msg_exit(char *msg, void *data);

/*
**	rendering
*/
void		render(t_mlx *mlx, t_data *data);
void		render_offscreen(t_data *data);
void		launch_threads(t_data *data);
int			get_col(int iter);
void		export_bmp(t_data *data);

void	*draw_mandel(void *thread_data);
void	*draw_julia(void *thread_data);
void	*draw_slow_mandel(void *thread_data);
void	*draw_slow_julia(void *thread_data);

/*
**	Operations on t_complex type
*/
void		fill_complex(t_complex *c, float re, float im);
float		squared_modulus(t_complex *z);
t_complex	*sum_c(t_complex *z, t_complex *add);
t_complex	*mult_c(t_complex *z, t_complex *mult);
t_complex	*square_c(t_complex *z);

/*
**	Mlx hooks
*/
int			mouse_pos(int x, int y, void *param);
int			mouse_click(int x, int y, int keycode, void *param);
int			keypress(int keycode, void *param);

#endif