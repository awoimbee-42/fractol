/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:49:02 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/10 23:18:14 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		join_threads(t_thread *threads)
{
	int			i;

	i = -1;
	while (++i < THREADS_NB)
	{
		if (pthread_join(threads[i].thread, NULL))
			msg_exit("Could not join thread nb %d.", &i);
	}
}

void		launch_threads(t_env *data)
{
	int			i;
	t_complex	derr_pc;
	t_complex	c;

	derr_pc.re = (1. / data->res.w) * data->thickness;
	derr_pc.im = 0;
	c.re = (data->mouse.re) * 2. - 1.;
	c.im = (data->mouse.im) * 2. - 1.;
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].data = data;
		data->threads[i].derr_pc = derr_pc;
		data->threads[i].c = c;
		data->threads[i].line_start = (i * data->res.h) / THREADS_NB;
		data->threads[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
		pthread_create(&data->threads[i].thread, NULL, data->fract, &data->threads[i]);
	}
	join_threads(data->threads);
}
