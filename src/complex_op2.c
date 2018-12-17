/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:17:55 by arthur            #+#    #+#             */
/*   Updated: 2018/12/17 19:38:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex		*c_swap(t_complex *c1, t_complex *c2)
{
	t_floating	tmp;

	tmp = c1->re;
	c1->re = c2->re;
	c2->re = tmp;
	tmp = c1->im;
	c1->im = c2->im;
	c2->im = tmp;
	return (c2);
}

t_complex		*c_abs(t_complex *c)
{
	c->re = fabs(c->re);
	c->im = fabs(c->im);
	return (c);
}
