/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cos_mandel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:54:44 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/13 02:00:13 by arthur           ###   ########.fr       */
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
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;

	env = ((t_thread*)thread_data)->env;
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
			draw_px(z, z, &env->mlx->img.px[px_id]);
			px_id++;
		}
	}
	return (NULL);
}
