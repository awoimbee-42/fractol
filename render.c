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

/*
**	find if point is part of the cardioide
**	find if point is part of bourgeon principal
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

static void	actually_render(t_data *data)
{
	t_pixel		px;
	t_complex	c;
	t_complex	z;
	double		z_re_square;
	double		z_im_square;
	int			iter;

	px.im_y = -1;
	while (++px.im_y < data->win_height)
	{
		px.re_x = -1;
		while (++px.re_x < data->win_width)
		{
			c.im = (px.im_y - (data->win_width / 2));
			c.re = (px.re_x - (data->win_height / 2));
			if (is_mandelbrot(c))
				data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = 0xFFFFFF;
			else
			{
				iter = 0;
				z.re = 0;
				z.im = 0;
				z_re_square = z.re * z.re;
				z_im_square = z.im * z.im;
				while ((z_re_square + z_im_square) <= 4. && iter < 500)
				{
					++iter;
					z.im = pow(z.re + z.im, 2.) - z_re_square - z_im_square;
					z.im += c.im;
					z.re = z_re_square - z_im_square + c.re;
					z_re_square = pow(z.re, 2.);
					z_im_square = pow(z.im, 2.);
				}
				data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = ((z_re_square + z_im_square) / 4);
			}
		}
	}
	fprintf(stderr, "rendered ?\n");
}

void		render(t_mlx *mlx, t_data *data)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->win_width, data->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
											&mlx->img.line_s, &mlx->img.endian);
	actually_render(data);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}