/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slow_mandel_julia.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:42:59 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/17 16:43:42 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_px(t_complex z, t_complex c, int iter_max, int *imgd)
{
	int			iter;
	int			col;

	iter = 0;
	col = 0x000000;
	while (++iter < iter_max)
	{
		if (c_squared_modulus(&z) > 100 && (col = blu_col(iter)))
			break ;
		(void)c_sum(c_square(&z), &c);
	}
	*imgd = col;
}

void		*draw_slow_mandel(void *thread_data)
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
			draw_px(z, z, env->iter_max, &env->mlx->img.px[px_id++]);
		}
	}
	return (NULL);
}

void		*draw_slow_julia(void *thread_data)
{
	t_env		*env;
	int			*i_d;
	int			pid;
	t_pixel		px;
	t_complex	z;

	env = ((t_thread*)thread_data)->env;
	i_d = env->mlx->img.px;
	px.im_y = ((t_thread*)thread_data)->line_start;
	pid = ((t_thread*)thread_data)->line_start * env->res.w;
	while (++px.im_y < ((t_thread*)thread_data)->line_end)
	{
		z.im = (px.im_y - (env->res.w / 2.)) / env->res.w
			* 5. * env->zoom + env->pos.im;
		px.re_x = -1;
		while (++px.re_x < env->res.w)
		{
			z.re = (px.re_x - (env->res.w / 2.)) / env->res.w
				* 5. * env->zoom + env->pos.re;
			draw_px(z, env->c, env->iter_max, &i_d[pid++]);
		}
	}
	return (NULL);
}
