/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:38:08 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/12 02:26:06 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		set_close(void *d)
{
	t_env	*data;

	data = (t_env*)d;
	data->iter_max = 0;
	return (0);
}

int		keypress(int keycode, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	keycode == K_W ? data->zoom /= 1.25 : 0;
	keycode == K_S ? data->zoom *= 1.25 : 0;
	keycode == K_LFT ? data->pos.re -= data->zoom : 0;
	keycode == K_RGT ? data->pos.re += data->zoom : 0;
	keycode == K_UP ? data->pos.im -= data->zoom : 0;
	keycode == K_DWN ? data->pos.im += data->zoom : 0;
	keycode == K_R ? render_offscreen(data) : 0;
	if (keycode == K_PLS)
		data->iter_max += 10;
	if (keycode == K_MNS && data->iter_max > 10)
		data->iter_max -= 10;
	keycode == K_ESC ? set_close(param) : 0;
	return (1);
}

int		mouse_pos(int x, int y, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	if ((data->fract == &draw_julia || data->fract == &draw_slow_julia)
	&& x > 0 && x < data->res.w
	&& y > 0 && y < data->res.w)
	{
		data->mouse.im = (t_floating)y / data->res.h;
		data->mouse.re = (t_floating)x / data->res.w;
	}
	return (1);
}

int		mouse_click(int keycode, int x, int y, void *param)
{
	t_env	*data;

	data = (t_env*)param;
	if (x > 0 && x < data->res.w && y > 0 && y < data->res.w)
	{
		if (keycode == MOUSE_ZOOM_IN)
		{
			data->zoom /= 1.3;
			data->iter_max += 1;
			data->pos.im += (y - (data->res.h / 2.)) / data->res.h * data->zoom
			* 1.5;
			data->pos.re += (x - (data->res.w / 2.L)) / data->res.w * data->zoom
			* 1.5;
		}
		else if (keycode == MOUSE_ZOOM_OUT && data->zoom < 1)
		{
			data->zoom *= 1.3;
			data->iter_max -= 1;
		}
	}
	return (1);
}

int		loop(void *d)
{
	t_env	*data;

	data = (t_env*)d;
	if (!data->iter_max)
		exit(EXIT_SUCCESS);
	render(data->mlx, data);
	return (0);
}
