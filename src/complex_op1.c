/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:55:36 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/02 22:39:07 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	*c_cos(t_complex *c)
{
	double	re;

	re = c->re;
	c->re = cos(c->re) * cosh(c->im);
	c->im = -1 * sin(re) * sinh(c->im);
	return (c);
}

t_complex		*c_sub(t_complex *z, t_complex *sub)
{
	z->re -= sub->re;
	z->im -= sub->im;
	return (z);
}

t_complex	*c_divide(t_complex *c, t_complex *divi)
{
	double	re;

	re = c->re;
	c->re = ((c->re * divi->re) + (c->im * divi->im))
			/ ((divi->re * divi->re) + (divi->im * divi->im));
	c->im = ((c->im * divi->re) - (re * divi->im))
			/ ((divi->re * divi->re) + (divi->im * divi->im));
	return (c);
}
