/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_burningship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:33:39 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/03 15:24:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
**	colors are : not enought iter, intside, then outside
*/

static void	draw_px(t_complex z, t_complex c, int *imgd)
{
	int			iter;
	t_complex	derr_inec;
	float		radius;

	derr_inec.re = 1;
	derr_inec.im = 0;
	iter = 0;
	while (++iter < ITER_MAX)
	{
		radius = c_squared_modulus(&z);
		if (c_squared_modulus(&derr_inec) < 0.001 && (iter = ITER_MAX))
			break ;
		if (radius > 100)
			break ;
		(void)c_mult(c_sum(&derr_inec, &derr_inec), &z);
		z.re = fabs(z.re);
		z.im = fabs(z.im);
		(void)c_sum(c_square(&z), &c);
	}
	*imgd = red_col(iter);
}

void		*draw_burningship(void *thread_data)
{
	t_thrd_data	*tdata;
	int			*img_data;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	tdata = (t_thrd_data*)thread_data;
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
			draw_px(z, z, &img_data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
