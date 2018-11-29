/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:50:12 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/29 18:05:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


/*
**	Function to find if we are inside the mandelbrot bulb
**	Using this speeds up the algo a LOT because without this it needs to :
**	compute until MAX_ITER
**	Thanks, wikipedia !
*/

static int	is_mandelbrot(t_complex *c)
{
	double			q;

	q = ((c->re-0.25) * (c->re-0.25) + c->im * c->im);
	if (q * (q + (c->re - 0.25)) < 0.25 * (c->im * c->im))
		return (1);
	if (((c->re + 1.) * (c->re + 1.) + c->im * c->im) < 1./16.)
		return (1);
	return (0);
}



/*
**	derr_pc = (P⁰)'(c)
**	derr_inpc  = (Pⁿ)'(c)
*/

//31 lignes
static void	draw_px(t_data *data, t_pixel px, int color, int iter)
{
	t_complex	c;
	t_complex	z;
	t_complex	derr_inpc;
	t_complex	derr_pc;
	t_complex	derr_enpc;

	c.im = (px.im_y - (data->win_width / 2.)) / data->win_width * 5. * data->zoom + data->pos_y;
	c.re = (px.re_x - (data->win_height / 2.)) / data->win_height * 5. * data->zoom + data->pos_x;
	z = c;
	fill_complex(&derr_pc, (1./data->win_width) * data->thickness, 0.);
	derr_inpc = derr_pc;
	fill_complex(&derr_enpc, 1., 0.);
	iter = 0;
	color = 0xFFFFFF;  //not enough iterations
	if (1==1 || !is_mandelbrot(&c))
	{
		while (++iter < 100000)
		{
			if (squared_modulus(&derr_enpc) < 0.001 && (color = 0xFF0000)) // inside colour
				break ;
			if (squared_modulus(&z) < squared_modulus(&derr_inpc) && (color = 0xFFFF00))  //contour
				break ;
			if (squared_modulus(&z) > 100*100 && (color = get_col(iter))) // outside color
				break ;
			(void)sum_c(mult_c(sum_c(&derr_inpc, &derr_inpc), &z), &derr_pc);
			(void)mult_c(sum_c(&derr_enpc, &derr_enpc), &z);
			(void)sum_c(square_c(&z), &c);
		}
	}
	data->mlx->img.data[(px.im_y * data->win_width + px.re_x)] = color;
}

void		render_mandelbrot(t_data *data)
{
	t_pixel		px;
	int			iter;
	int			color;

	iter = 0;
	color = 0xFFFFFF;
	px.im_y = -1;
	while (++px.im_y < data->win_height)
	{
		px.re_x = -1;
		while (++px.re_x < data->win_width)
		{
			draw_px(data, px, color, iter);
		}
	}
}
