/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:42:31 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/15 01:16:57 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			c_fill(t_complex *c, float re, float im)
{
	c->re = re;
	c->im = im;
}

double			c_squared_modulus(t_complex *z)
{
	return (z->re * z->re + z->im * z->im);
}

t_complex		*c_sum(t_complex *z, t_complex *add)
{
	z->re += add->re;
	z->im += add->im;
	return (z);
}

t_complex		*c_mult(t_complex *z, t_complex *mult)
{
	typeof(z->re)	re;

	re = z->re;
	z->re = z->re * mult->re - z->im * mult->im;
	z->im = z->im * mult->re + re * mult->im;
	return (z);
}

t_complex		*c_square(t_complex *z)
{
	typeof(z->re)	re;

	re = z->re;
	z->re = z->re * z->re - z->im * z->im;
	z->im = z->im * re * 2;
	return (z);
}
