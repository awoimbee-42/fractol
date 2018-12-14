/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cos_mandel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:54:44 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/14 11:43:00 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	draw_px(t_complex z, t_complex c, int iter_max, int *imgd)
{
	int			iter;
	int			col;

	iter = 0;
	col = 0xFFFFFF;
	while (++iter < iter_max)
	{
		if (c_squared_modulus(&z) > 50 && (col = blu_col(iter)))
			break ;
		(void)c_cos(c_divide(&z, &c));
	}
	*imgd = col;
	return (1);
}

void		*draw_cos_mandel(void *thread_data)
{
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;
	t_complex	zstep;

	env = ((t_thread*)thread_data)->env;
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	zstep = (t_c){(5. * env->zoom) / env->res.w, (5. * env->zoom) / env->res.w};
	z.im = ((px.im_y - (env->res.w / 2.)) / env->res.w)
	* 5. * env->zoom + env->pos.im;
	while (++px.im_y < ((t_thread*)thread_data)->line_end && (px.re_x = -1))
	{
		z.re = (-2.5 * env->zoom + env->pos.re);
		while (++px.re_x < env->res.w)
			if (draw_px((t_c){0, 0}, z,
				env->iter_max, &env->mlx->img.px[px_id++]))
				z.re += zstep.re;
		z.im += zstep.im;
	}
	return (NULL);
}
