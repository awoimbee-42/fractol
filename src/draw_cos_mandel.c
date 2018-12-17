/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cos_mandel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:54:44 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/17 19:54:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <time.h>

static void	draw_px(t_complex z, t_complex c, int iter_max, int *imgd)
{
	int			iter;
	int			col;
	t_complex	derr_inpc;
	t_complex	tmp;

	derr_inpc = z;
	iter = 0;
	col = 0xFFFFFF;
	while (++iter < iter_max)
	{
		if ((derr_inpc.re * derr_inpc.re + derr_inpc.im * derr_inpc.im) < 0.1)
			break ;
		if ((z.re * z.re + z.im * z.im) > 10000 && (col = blu_col(iter)))
			break ;
		tmp = derr_inpc;
		derr_inpc = z;
		(void)c_mult(c_div(c_opsite(c_sin(c_div(&derr_inpc, &c))), &c), &tmp);
		(void)c_cos(c_div(&z, &c));
	}
	*imgd = col;
}

void		*draw_cos_mandel(void *thread_data)
{
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	env = ((t_thread*)thread_data)->env;
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	z.im = ((px.im_y - (env->res.w / 2.)) / env->res.w)
	* 5. * env->zoom + env->pos.im;
	while (++px.im_y < ((t_thread*)thread_data)->line_end && (px.re_x = -1))
	{
		z.re = (-2.5 * env->zoom + env->pos.re);
		while (++px.re_x < env->res.w)
		{
			draw_px((t_c){1, 0}, z, env->iter_max, &env->mlx->img.px[px_id++]);
			z.re += env->z_step.re;
		}
		z.im += env->z_step.im;
	}
	return (NULL);
}
