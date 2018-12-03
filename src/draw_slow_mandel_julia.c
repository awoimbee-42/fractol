/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slow_mandel_julia.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:42:59 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/03 15:31:22 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_px(t_complex z, t_complex c, int *imgd)
{
	int			iter;
	int			col;

	iter = 0;
	col = 0x000000;
	while (++iter < ITER_MAX)
	{
		if (c_squared_modulus(&z) > 100 && (col = red_col(iter)))
			break ;
		(void)c_sum(c_square(&z), &c);
	}
	*imgd = col;
}

void		*draw_slow_mandel(void *thread_data)
{
	t_thrd_data	*tdata;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	tdata = (t_thrd_data*)thread_data;
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

void		*draw_slow_julia(void *thread_data)
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
			draw_px(z, tdata->c, &img_data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
