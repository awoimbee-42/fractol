/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:50:12 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/30 19:27:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
**	colors are : not enought iter, intside, then outside
*/

static void	draw_px(t_complex z, t_complex c, t_complex derr_pc, int *imgd)
{
	int			iter;
	int			col;
	t_complex	derr_inpc;
	t_complex	derr_inec;
	float		radius;

	derr_inpc = derr_pc;
	derr_inec.re = 1;
	derr_inec.im = 0;
	iter = 0;
	col = 0xF0F0FF;
	while (++iter < 500)
	{
		radius = squared_modulus(&z);
		if (squared_modulus(&derr_inec) < 0.001 && (col = get_col(iter)))
			break ;
		if (radius < squared_modulus(&derr_inpc) && (col = 0xFFFFFF))
			break ;
		if (radius > 100 && (col = get_col(iter)))
			break ;
		(void)sum_c(mult_c(sum_c(&derr_inpc, &derr_inpc), &z), &derr_pc);
		(void)mult_c(sum_c(&derr_inec, &derr_inec), &z);
		(void)sum_c(square_c(&z), &c);
	}
	*imgd = col;
}

void		render_fract(t_data *data)
{
	t_pixel		px;
	t_complex	c;
	t_complex	z;
	t_complex	derr_pc;
	int			px_id;

	derr_pc.re = (1. / data->res.w) * data->thickness;
	derr_pc.im = 0;
	px.im_y = -1;
	c.re = (data->mouse.re) * 2. - 1.;
	c.im = (data->mouse.im) * 2. - 1.;
	fprintf(stderr, "c.re %f\t\tc.im %f\n", c.re, c.im);
	while (++px.im_y < data->res.h)
	{
		px.re_x = -1;
		while (++px.re_x < data->res.w)
		{
			px_id = px.im_y * data->res.w + px.re_x;
			z.im = (px.im_y - (data->res.w / 2.)) / data->res.w
			* 5. * data->zoom + data->pos.im;
			z.re = (px.re_x - (data->res.w / 2.)) / data->res.w
			* 5. * data->zoom + data->pos.re;
			if (data->fract)
				draw_px(z, z, derr_pc, &data->mlx->img.data[px_id]);
			else
				draw_px(z, c, derr_pc, &data->mlx->img.data[px_id]);
		}
	}
}
