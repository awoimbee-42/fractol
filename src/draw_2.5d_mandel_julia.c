/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.5d_mandel_julia.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:50:12 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/17 19:54:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Default mandelbrot & julia representation
*/

static int		pimp_colors(t_complex *z, t_complex *derr_inpc, int iter)
{
	int			color;

	color = 0;
	if (iter != 500)
	{
		(void)c_div(z, derr_inpc);
		*derr_inpc = *z;
		(void)c_div(z, c_abs(derr_inpc));
		z->re = z->re * 0.7071067811865475 + z->im * 0.7071067811865475 + 1.5;
		z->re = z->re / (1 + 1.5);
		z->re = z->re < 0 ? 0 : z->re;
		color = 150 * z->re + 105;
		color = color + (color << 8) + (color << 16);
	}
	return (color);
}

/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
**	colors are : not enought iter, intside, then outside
*/

static int		draw_px(t_complex z, t_complex *c, float thickness, int *imgd)
{
	int			iter;
	t_complex	derr_inec;
	t_complex	derr_inpc;
	float		sqrmod_z;

	derr_inec = (t_c){1, 0};
	derr_inpc = (t_c){thickness, 0};
	iter = 0;
	while (++iter < 500)
	{
		sqrmod_z = (z.re * z.re + z.im * z.im);
		if (sqrmod_z < c_squared_modulus(&derr_inpc) && (iter = 500))
			break ;
		if (c_squared_modulus(&derr_inec) < 0.001 && (iter = 500))
			break ;
		if (sqrmod_z > 500)
			break ;
		(void)c_mult(c_sum(&derr_inec, &derr_inec), &z);
		(void)c_mult(c_sum(&derr_inpc, &derr_inpc), &z);
		derr_inpc.re += thickness;
		(void)c_sum(c_square(&z), c);
	}
	*imgd = pimp_colors(&z, &derr_inpc, iter);
	return (1);
}

static float	get_thickness(int iter_m)
{
	t_floating	res;

	res = 1;
	while (iter_m > 0)
	{
		res /= 1.5;
		iter_m -= 2;
	}
	return (res);
}

void			*draw_mandel(void *thread_data)
{
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;
	float		thickness;

	env = ((t_thread*)thread_data)->env;
	thickness = get_thickness(env->iter_max);
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	z.im = ((px.im_y - (env->res.w / 2.)) / env->res.w)
	* 5. * env->zoom + env->pos.im;
	while (++px.im_y < ((t_thread*)thread_data)->line_end && !(px.re_x = 0))
	{
		z.re = (-2.5L * env->zoom + env->pos.re);
		while (px.re_x++ < env->res.w)
		{
			draw_px(z, &z, thickness, &env->mlx->img.px[px_id++]);
			z.re += env->z_step.re;
		}
		z.im += env->z_step.im;
	}
	return (NULL);
}

void			*draw_julia(void *thread_data)
{
	t_env		*env;
	int			px_id;
	t_pixel		px;
	t_complex	z;
	t_floating	thickness;

	env = ((t_thread*)thread_data)->env;
	thickness = get_thickness(env->iter_max);
	px.im_y = ((t_thread*)thread_data)->line_start;
	px_id = ((t_thread*)thread_data)->line_start * env->res.w;
	z.im = ((px.im_y - (env->res.w / 2.)) / env->res.w)
	* 5. * env->zoom + env->pos.im;
	while (++px.im_y < ((t_thread*)thread_data)->line_end && !(px.re_x = 0))
	{
		z.re = (-2.5 * env->zoom + env->pos.re);
		while (px.re_x++ < env->res.w)
		{
			draw_px(z, &env->c, thickness, &env->mlx->img.px[px_id++]);
			z.re += env->z_step.re;
		}
		z.im += env->z_step.im;
	}
	return (NULL);
}
