/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:49:02 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/15 01:22:47 by arthur           ###   ########.fr       */
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

	c.re = (data->mouse.re) * 2.L - 1.L;
	c.im = (data->mouse.im) * 2.L - 1.L;
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].c = c;
		pthread_create(&data->threads[i].thread, NULL, data->fract, &data->threads[i]);
	}
	join_threads(data->threads);
}
