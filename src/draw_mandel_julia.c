/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel_julia.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:50:12 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/10 23:23:47 by awoimbee         ###   ########.fr       */
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
	col = 0xFFFFFF;
	while (++iter < ITER_MAX)
	{
		radius = c_squared_modulus(&z);
		if (c_squared_modulus(&derr_inec) < 0.001 && (col = 0xFFFFFF))
			break ;
		if (radius < c_squared_modulus(&derr_inpc) && (col = 0xFFFFFF))
			break ;
		if (radius > 100 && (col = blu_col(iter)))
			break ;
		(void)c_sum(c_mult(c_sum(&derr_inpc, &derr_inpc), &z), &derr_pc);
		(void)c_mult(c_sum(&derr_inec, &derr_inec), &z);
		(void)c_sum(c_square(&z), &c);
	}
	*imgd = col;
}

void		*draw_mandel(void *thread_data)
{
	t_thread	*tdata;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	tdata = (t_thread*)thread_data;
	px.im_y = tdata->line_start;
	px_id = tdata->line_start * tdata->data->res.w;
	while (++px.im_y < tdata->line_end)
	{
		z.im = (px.im_y - (tdata->data->res.w / 2.)) / tdata->data->res.w
			* 5. * tdata->data->zoom + tdata->data->pos.im;
		px.re_x = -1;
		while (++px.re_x < tdata->data->res.w)
		{
			z.re = (px.re_x - (tdata->data->res.w / 2.)) / tdata->data->res.w
				* 5. * tdata->data->zoom + tdata->data->pos.re;
			draw_px(z, z, tdata->derr_pc, &tdata->data->mlx->img.data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}

void		*draw_julia(void *thread_data)
{
	t_thread	*tdata;
	int			*img_data;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	tdata = (t_thread*)thread_data;
	img_data = tdata->data->mlx->img.data;
	px.im_y = tdata->line_start;
	px_id = tdata->line_start * tdata->data->res.w;
	while (++px.im_y < tdata->line_end)
	{
		z.im = (px.im_y - (tdata->data->res.w / 2.)) / tdata->data->res.w
			* 5. * tdata->data->zoom + tdata->data->pos.im;
		px.re_x = -1;
		while (++px.re_x < tdata->data->res.w)
		{
			z.re = (px.re_x - (tdata->data->res.w / 2.)) / tdata->data->res.w
				* 5. * tdata->data->zoom + tdata->data->pos.re;
			draw_px(z, tdata->c, tdata->derr_pc, &img_data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
