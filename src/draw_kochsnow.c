/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_kochsnow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:57:01 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/05 14:35:27 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_line_higrad(t_pixel p0, t_pixel p1, int *img, int win_w)
{
	t_pixel		delta;
	int			way_x;
	int			error;

	delta.re_x = p1.re_x - p0.re_x;
	delta.im_y = p1.im_y - p0.im_y;
	way_x = 1;
	if (delta.re_x < 0 && (delta.re_x *= -1))
		way_x = -1;
	error = 2 * delta.re_x - delta.im_y;
	while (p0.im_y < p1.im_y)
	{
		img[(p0.im_y * win_w + p0.re_x)] = 0xFFFFFF;
		if (error > 0)
		{
			p0.re_x += way_x;
			error -= 2 * delta.im_y;
		}
		error += 2 * delta.re_x;
		++p0.im_y;
	}
}

static void	draw_line_lograd(t_pixel p0, t_pixel p1, int *img, int win_w)
{
	t_pixel		delta;
	int			way_y;
	int			error;

	delta.re_x = p1.re_x - p0.re_x;
	delta.im_y = p1.im_y - p0.im_y;
	way_y = 1;
	if (delta.im_y < 0 && (delta.im_y *= -1))
		way_y = -1;
	error = 2 * delta.im_y - delta.re_x;
	while (p0.re_x < p1.re_x)
	{
		img[(p0.im_y * win_w + p0.re_x)] = 0xFFFFFF;
		if (error > 0)
		{
			p0.im_y += way_y;
			error -= 2 * delta.re_x;
		}
		error += 2 * delta.im_y;
		++p0.re_x;
	}
}

static void	draw_line(t_pixel p0, t_pixel p1, int *img, int win_w)
{
	if (abs(p1.im_y - p0.im_y) < abs(p1.re_x - p0.re_x))
	{
		if (p0.re_x > p1.re_x)
			draw_line_lograd(p1, p0, img, win_w);
		else
			draw_line_lograd(p0, p1, img, win_w);
	}
	else
	{
		if (p0.im_y > p1.im_y)
			draw_line_higrad(p1, p0, img, win_w);
		else
			draw_line_higrad(p0, p1, img, win_w);
	}
}

void		compute_koch(t_complex p1, t_complex p2, int times, t_env *env)
{
	t_complex	p3;
	t_complex	p4;
	t_complex	p5;
	double		theta;

	theta = 3.14159265358979323846 / 3.;
	if (times > 0)
	{
		p3 = (t_complex){(2 * p1.re + p2.re) / 3, (2 * p1.im + p2.im) / 3};
		p5 = (t_complex){(2 * p2.re + p1.re) / 3, (2 * p2.im + p1.im) / 3};
		p4 = (t_complex){
			p3.re + (p5.re - p3.re) * cos(theta) + (p5.im - p3.im) * sin(theta),
			p3.im - (p5.re - p3.re) * sin(theta) + (p5.im - p3.im) * cos(theta)
		};
		compute_koch(p1, p3, times - 1, env);
		compute_koch(p3, p4, times - 1, env);
		compute_koch(p4, p5, times - 1, env);
		compute_koch(p5, p2, times - 1, env);
	}
	else if ((int)p1.re > -1 && (int)p1.re < env->res.w - 1
			&& (int)p2.re > -1 && (int)p2.re < env->res.w - 1
			&& (int)p1.im > -1 && (int)p1.im < env->res.h - 1
			&& (int)p2.im > -1 && (int)p2.im < env->res.h - 1)
		draw_line((t_pixel){p1.re, p1.im}, (t_pixel){p2.re, p2.im},
		env->mlx->img.px, env->res.w);
}

void		*draw_koch(void *data)
{
	t_complex	p_start;
	t_complex	p_end;
	t_env		*env;

	env = data;
	p_start = (t_c){-env->pos.re * 3,
	((env->res.h / 2.) - env->pos.im * 3)};
	p_end = (t_c){(env->res.w) / env->zoom - env->pos.re * 3,
	(env->res.h / 2.) - env->pos.im * 3};
	compute_koch(p_start, p_end, env->iter_max / 10, env);
	return (NULL);
}
