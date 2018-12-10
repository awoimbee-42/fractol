/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cos_mandel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:54:44 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/10 23:23:47 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_px(t_complex z, t_complex c, int *imgd)
{
	int			iter;
	int			col;

	iter = 0;
	col = 0xFFFFFF;
	z.re = 0;
	z.im = 0;
	while (++iter < ITER_MAX)
	{
		if (c_squared_modulus(&z) > 50 && (col = blu_col(iter)))
			break ;
		(void)c_cos(c_divide(&z, &c));
	}
	*imgd = col;
}

void		*draw_cos_mandel(void *thread_data)
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
			draw_px(z, z, &tdata->data->mlx->img.data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
