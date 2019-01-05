/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:42:31 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/05 14:44:30 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex		*c_sum(t_complex *z, t_complex *c)
{
	z->re += c->re;
	z->im += c->im;
	return (z);
}

t_complex		*c_mult(t_complex *z, t_complex *c)
{
	t_floating	re;

	re = z->re;
	z->re = z->re * c->re - z->im * c->im;
	z->im = z->im * c->re + re * c->im;
	return (z);
}

t_complex		*c_square(t_complex *z)
{
	t_floating	re;

	re = z->re;
	z->re = z->re * z->re - z->im * z->im;
	z->im = (z->im * re) * 2;
	return (z);
}
