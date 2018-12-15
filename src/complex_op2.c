/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 00:17:55 by arthur            #+#    #+#             */
/*   Updated: 2018/12/15 01:19:10 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex		*c_swap(t_complex *c1, t_complex *c2)
{
	typeof(c1->re)	tmp;

	tmp = c1->re;
	c1->re = c2->re;
	c2->re = tmp;
	tmp = c1->im;
	c1->im = c2->im;
	c2->im = tmp;
	return (c2);
}
