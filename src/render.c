/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:26:53 by marvin            #+#    #+#             */
/*   Updated: 2018/11/26 23:26:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h> //  !!!!!!!


/*
**	Function to find if we are inside the mandelbrot bulb
**	Using this speeds up the algo a LOT because without this it needs to :
**	compute until MAX_ITER
*/

static int	is_mandelbrot(t_complex c)
{
	double			tmp;
	double			p;

	p = sqrt(((c.re-0.25) * (c.re-0.25)) + c.im * c.im);
	tmp = p - (2. * p * p) + 0.25;
	if (c.re < tmp)
		return (1);
	tmp = (c.re + 1.) * (c.re + 1.) + c.im * c.im;
	if (tmp < 1./16.)
		return (1);
	return (0);
}

double			squared_modulus(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}

t_complex		sum_c(t_complex z, t_complex add)
{
	z.re += add.re;
	z.im += add.im;
	return (z);
}

t_complex		mult_c(t_complex z, t_complex mult)
{
	t_complex	result;

	result.re = z.re * mult.re - z.im * mult.im;
	result.im = z.im * mult.re + z.re * mult.im;
	return (result);
}

int			get_col(int iter)
{
	return ((0x0000F * iter) & 0xFFFFFF);
}

t_complex		fill_complex(float re, float im)
{
	t_complex	result;

	result.re = re;
	result.im = im;
	return (result);
}

/*
**	// derr_pc = (P⁰)'(c) NO
**	derr_inpc  = (Pⁿ)'(c)
*/

static void	actually_render(t_data *data)
{
	t_pixel		px;
	t_complex	c;
	t_complex	z;
	int			iter;
	int			color;
	t_complex	derr_inpc;
	t_complex	derr_pc;
	t_complex	derr_enpc;

	float		thickness;

	thickness = 0.0001;
	px.im_y = -1;
	while (++px.im_y < data->win_height)
	{
		px.re_x = -1;
		while (++px.re_x < data->win_width)
		{
			c.im = (px.im_y - (data->win_width / 2.)) / data->win_width * 5. * data->zoom + data->pos_y;
			c.re = (px.re_x - (data->win_height / 2.)) / data->win_height * 5. * data->zoom + data->pos_x;
			z = c;

			derr_pc = fill_complex((1./data->win_width)* thickness, 0.);
			derr_inpc = derr_pc;
			derr_enpc = fill_complex(1., 0.);
			iter = 0;
			color = 0xFFFFFF;  //not enough iterations
			if (!is_mandelbrot(c))
			{
				while (++iter < 500)
				{
					if (squared_modulus(derr_enpc) < 0.01 && (color = 0xFF0000)) // inside colour
						break ;
					if (squared_modulus(z) < squared_modulus(derr_inpc) && (color = 0xFFFF00))  //contour
						break ;
					if (squared_modulus(z) > 100*100 && (color = get_col(iter))) // outside color
						break ;
					derr_inpc = sum_c(mult_c(sum_c(derr_inpc, derr_inpc), z), derr_pc);
					derr_enpc = mult_c(sum_c(derr_enpc, derr_enpc), z);
					z = sum_c(mult_c(z, z), c);
				}
			}
			data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = color;
		}
	}
}

void		render(t_mlx *mlx, t_data *data)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->win_width, data->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
											&mlx->img.line_s, &mlx->img.endian);
	clock_t begin = clock();
	actually_render(data);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	fprintf(stderr, "time spend calculating frame : %f\n", time_spent);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}