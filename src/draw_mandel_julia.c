/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel_julia.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:50:12 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/16 21:06:00 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
**	colors are : not enought iter, intside, then outside
*/

static int	draw_px(t_complex z, t_complex c, int iter_max, int *imgd)
{
	int			iter;
	int			col;
	t_complex	derr_inec;

	derr_inec.re = 1.L;
	derr_inec.im = 0.L;
	iter = 0;
	col = 0xFFFFFF;
	while (++iter < iter_max)
	{
		if ((derr_inec.re * derr_inec.re + derr_inec.im * derr_inec.im) < 0.001)
			break ;
		if ((z.re * z.re + z.im * z.im) > 100. && (col = blu_col(iter)))
			break ;
		(void)c_mult(c_sum(&derr_inec, &derr_inec), &z);
		(void)c_sum(c_square(&z), &c);
	}
	*imgd = col;
	return (1);
}

void		*draw_mandel(void *thread_data)
{
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;
	t_complex	zstep;

	env = ((t_thread*)thread_data)->env;
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	zstep = (t_c){(env->zoom * 5.) / env->res.w, (5. * env->zoom) / env->res.w};
	z.im = ((px.im_y - (env->res.w / 2.)) / env->res.w)
	* 5. * env->zoom + env->pos.im;
	while (++px.im_y < ((t_thread*)thread_data)->line_end && (px.re_x = -1))
	{
		z.re = (-2.5L * env->zoom + env->pos.re);
		while (++px.re_x < env->res.w)
			if (draw_px(z, z, env->iter_max, &env->mlx->img.px[px_id++]))
				z.re += zstep.re;
		z.im += zstep.im;
	}
	return (NULL);
}

void		*draw_julia(void *thread_data)
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
			if (draw_px(z, ((t_thread*)thread_data)->c,
				env->iter_max, &env->mlx->img.px[px_id++]))
				z.re += zstep.re;
		z.im += zstep.im;
	}
	return (NULL);
}
