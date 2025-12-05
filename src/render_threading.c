/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:49:02 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/31 03:58:38 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		launch_threads(t_env *data)
{
	int			i;

	if (data->fract == &draw_koch)
	{
		draw_koch(data);
		return ;
	}
	data->c.re = (data->mouse.re) * 2.L - 1.L;
	data->c.im = (data->mouse.im) * 2.L - 1.L;
	data->z_step = (t_c){(t_floating)(5 * data->zoom) / data->res.w,
						(t_floating)(5 * data->zoom) / data->res.w};
	i = -1;
	while (++i < THREADS_NB)
		pthread_create(&data->threads[i].thread, NULL,
		data->fract, &data->threads[i]);
	i = -1;
	while (++i < THREADS_NB)
		if (pthread_join(data->threads[i].thread, NULL))
			ft_msg_exit("Could not join thread nb %d.", &i);
}
