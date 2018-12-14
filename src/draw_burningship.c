/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_burningship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:33:39 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/13 02:28:33 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
**	colors are : not enought iter, intside, then outside
*/

static void	draw_px(t_complex z, t_complex c, int iter_max, int *imgd)
{
	int			iter;
	t_complex	derr_inec;
	float		radius;

	derr_inec.re = 1;
	derr_inec.im = 0;
	iter = 0;
	while (++iter < iter_max)
	{
		radius = c_squared_modulus(&z);
		if (c_squared_modulus(&derr_inec) < 0.001 && (iter = iter_max))
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
	t_env		*env;
	int			*img_data;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	env = ((t_thread*)thread_data)->env;
	img_data = env->mlx->img.px;
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	while (++px.im_y < ((t_thread*)thread_data)->line_end)
	{
		z.im = (px.im_y - (env->res.w / 2.)) / env->res.w
			* 5. * env->zoom + env->pos.im;
		px.re_x = -1;
		while (++px.re_x < env->res.w)
		{
			z.re = (px.re_x - (env->res.w / 2.)) / env->res.w
				* 5. * env->zoom + env->pos.re;
			draw_px(z, z, env->iter_max, &img_data[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
