/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:47:40 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/12 02:06:10 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	chaos(void *fate)
{
	if (fate == NULL)
		msg_exit("Doom is uppon us.\n(Could not create window)", 0);
}

void	print_instructions(void)
{
	ft_printf(
			" ------------------------------------------------------\n"
			"| Use the arrow keys to move around                    |\n"
			"| Use W & S or the scroll wheel to zoom in and out     |\n"
			"|     (scrolling also changes the precision)           |\n"
			"| Use + & - to change the branch precision             |\n"
			"|     (not on all fractals)                            |\n"
			" ------------------------------------------------------\n");
}
