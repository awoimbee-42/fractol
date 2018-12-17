/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:35:10 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/17 16:30:51 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			red_col(int iter)
{
	int		color;

	if (iter < 64)
		color = ((iter * 2) << 16);
	else if (iter < 128)
		color = ((((iter - 64) * 128) / 126) + 128) << 16;
	else if (iter < 256)
		color = ((((iter - 128) * 62) / 127) + 193) << 16;
	else if (iter < 512)
		color = 0xFF0000 + (((((iter - 256) * 62) / 255) + 1) << 8);
	else if (iter < 1024)
		color = 0xFF0000 + (((((iter - 512) * 63) / 511) + 64) << 8);
	else if (iter < 2048)
		color = 0xFF0000 + (((((iter - 1024) * 63) / 1023) + 128) << 8);
	else if (iter < 4096)
		color = 0xFF0000 + (((((iter - 2048) * 63) / 2047) + 192) << 8);
	else
		color = 0xFFFF00;
	return (color);
}

int			blu_col(int iter)
{
	return ((0x00000F * iter) & 0x0000FF);
}

void		render(t_mlx *mlx, t_env *data)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->res.w, data->res.h);
	mlx->img.px = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
											&mlx->img.line_s, &mlx->img.endian);
	launch_threads(data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}

void		render_offscreen(t_env *data)
{
	int		i;

	ft_printf("{ylw}Making high quality render...{eoc}\n");
	data->res.h *= OFFSCREEN_RES_FACTOR;
	data->res.w *= OFFSCREEN_RES_FACTOR;
	if (!(data->mlx->img.px = malloc((data->res.w * data->res.h) * 4)))
		msg_exit("Not enought ram!", 0);
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].line_start = (i * data->res.h) / THREADS_NB;
		data->threads[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
	}
	launch_threads(data);
	export_bmp(data);
	free(data->mlx->img.px);
	data->res.h /= OFFSCREEN_RES_FACTOR;
	data->res.w /= OFFSCREEN_RES_FACTOR;
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].line_start = (i * data->res.h) / THREADS_NB;
		data->threads[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
	}
	ft_printf("{grn}Render done, check img.bmp!{eoc}\n");
}
