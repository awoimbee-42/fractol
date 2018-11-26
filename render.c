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

static int	is_mandelbrot(t_pixel px)
{
	double			tmp;
	double			p;

	p = sqrt(pow(px.re_x-0.25, 2) + pow(px.im_y, 2));
	tmp = p - (2. * pow(p, 2.)) + 0.25;
	if (px.re_x < tmp)
		return (1);
	tmp = pow(px.re_x + 1., 2.) + pow(px.im_y, 2.);
	if (tmp < 1./16.)
		return (1);
	return (0);
}

static void	actually_render(t_data *data)
{
	t_pixel		px;

	px.im_y = -1;
	while (++px.im_y < data->win_height)
	{
		px.re_x = -1;
		while (++px.re_x < data->win_width)
		{
			if (is_mandelbrot(px))
				data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = 0xFFFFFF;
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