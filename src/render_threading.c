/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:49:02 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/02 20:01:55 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		join_threads(pthread_t *threads)
{
	int			i;

	i = -1;
	while (++i < THREADS_NB)
	{
		if (pthread_join(threads[i], NULL))
			msg_exit("Could not join thread nb %d.", &i);
	}
}

void		launch_threads(t_data *data)
{
	int			i;
	t_complex	derr_pc;
	t_complex	c;
	t_thrd_data	*thread_d;

	if (!(thread_d = malloc(sizeof(t_thrd_data) * THREADS_NB)))
		msg_exit("You ran out of memory.", 0);
	derr_pc.re = (1. / data->res.w) * data->thickness;
	derr_pc.im = 0;
	c.re = (data->mouse.re) * 2. - 1.;
	c.im = (data->mouse.im) * 2. - 1.;
	i = -1;
	while (++i < THREADS_NB)
	{
		thread_d[i].data = data;
		thread_d[i].derr_pc = derr_pc;
		thread_d[i].c = c;
		thread_d[i].line_start = (i * data->res.h) / THREADS_NB;
		thread_d[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
		pthread_create(&data->threads[i], NULL, data->fract, &thread_d[i]);
	}
	join_threads(data->threads);
	free(thread_d);
}
