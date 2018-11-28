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

	p = sqrt(pow(c.re-0.25, 2) + pow(c.im, 2));
	tmp = p - (2. * pow(p, 2.)) + 0.25;
	if (c.re < tmp)
		return (1);
	tmp = pow(c.re + 1., 2.) + pow(c.im, 2.);
	if (tmp < 1./16.)
		return (1);
	return (0);
}

double			squared_modulus(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}

t_complex		square_c(t_complex z)
{
	float		tmp;

	tmp = z.re;
	z.re = (z.re * z.re) - (z.im * z.im);
	z.im = 2 * tmp * z.im;
	return (z);
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

	result.re = z.re * mult.re + z.im * mult.im;
	result.im = z.re * mult.im + z.im * mult.re;
	return (result);
}

int			get_col(int iter)
{
	return ((0x0000F * iter) & 0xFFFFFF);
}

/*
** derr_inpc  = (Pⁿ)'(c)
*/

static void	actually_render(t_data *data)
{
	t_pixel		px;
	t_complex	c;
	t_complex	z;
	int			iter;
	int			color;
	t_complex	derr_inpc;

	px.im_y = -1;
	while (++px.im_y < data->win_height)
	{
		px.re_x = -1;
		while (++px.re_x < data->win_width)
		{
			c.im = (px.im_y - (data->win_width / 2.)) / data->win_width * 5. * data->zoom + data->pos_y;
			c.re = (px.re_x - (data->win_height / 2.)) / data->win_height * 5. * data->zoom + data->pos_x;
			z = c;
			derr_inpc.re = 1;
			derr_inpc.im = 0;
			iter = 0;
			color = 0x000000;  //not enough iterations
			if (1 == 1 || !is_mandelbrot(c))
			{
				while (++iter < 500)
				{
					if (squared_modulus(derr_inpc) < 0.000001)
					{
						color = 0xFFFF00; //inside color
						break ;
					}
					if (squared_modulus(z) > 4 && (color = get_col(iter))) // outside color
						break ;
					derr_inpc = mult_c(sum_c(derr_inpc, derr_inpc), z);
					z = sum_c(square_c(z), c);
				}
			}
			data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = color;
		}
	}
	fprintf(stderr, "rendered ?\n");
}

//weird fractal
// static void	actually_render(t_data *data)
// {
// 	t_pixel		px;
// 	t_complex	c;
// 	t_complex	z;
// 	double		z_re_square;
// 	double		z_im_square;
// 	int			iter;

// 	px.im_y = -1;
// 	while (++px.im_y < data->win_height)
// 	{
// 		px.re_x = -1;
// 		while (++px.re_x < data->win_width)
// 		{
// 			c.im = (px.im_y - (data->win_width / 2));
// 			c.re = (px.re_x - (data->win_height / 2));
// 			if (is_mandelbrot(c) && 1 == 0)
// 				data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = 0xFFFFFF;
// 			else
// 			{
// 				iter = 0;
// 				z = c;
// 				z_re_square = z.re * z.re;
// 				z_im_square = z.im * z.im;
// 				while ((z_re_square + z_im_square) <= 4. && iter < 500)
// 				{
// 					++iter;
// 					z.im = pow(z.re + z.im, 2.) - z_re_square - z_im_square;
// 					z.im += c.im;
// 					z.re = z_re_square - z_im_square + c.re;
// 					z_re_square = pow(z.re, 2.);
// 					z_im_square = pow(z.im, 2.);
// 				}
// 				data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = ((z_re_square + z_im_square) / 4);
// 			}
// 		}
// 	}
// 	fprintf(stderr, "rendered ?\n");
// }

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