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

# ifdef __APPLE__
#  define K_AUP 126
#  define K_DWN 125
#  define K_LFT 123
#  define K_RGT 124
#  define K_LEQ 12
#  define K_LEE 14
#  define K_LEW 13
#  define K_LES 1
#  define K_LEA 0
#  define K_LED 2
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

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_data
{
	t_mlx		*mlx;
	double		zoom;
	double		pos_x;
	double		pos_y;
	int			win_height;
	int			win_width;
}				t_data;

void		msg_exit(char *msg, void *data);
void		render(t_mlx *mlx, t_data *data);
void		chaos(void *fate);

#endif