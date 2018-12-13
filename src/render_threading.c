/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:49:02 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/13 02:10:11 by arthur           ###   ########.fr       */
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
	t_complex	c;

	c.re = (data->mouse.re) * 2. - 1.;
	c.im = (data->mouse.im) * 2. - 1.;
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].env = data;
		data->threads[i].c = c;
		data->threads[i].line_start = (i * data->res.h) / THREADS_NB;
		data->threads[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
		pthread_create(&data->threads[i].thread, NULL, data->fract, &data->threads[i]);
	}
	join_threads(data->threads);
}
