/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:35:10 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/02 17:47:41 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			get_col(int iter)
{
	return ((0x0000F * iter) & 0xFFFFFF);
}

void		render(t_mlx *mlx, t_data *data)
{
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->res.w, data->res.h);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
											&mlx->img.line_s, &mlx->img.endian);
	launch_threads(data);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
}

void		render_offscreen(t_data *data)
{
	t_res	tmp_res;

	write(1, "Making high quality render...\n", 30);
	tmp_res = data->res;
	data->res.h = 10000;
	data->res.w = 10000;
	if (!(data->mlx->img.data = malloc((data->res.w * data->res.h) * 4)))
		msg_exit("Not enought ram!", 0);
	launch_threads(data);
	export_bmp(data);
	free(data->mlx->img.data);
	data->res = tmp_res;
	write(1, "Render done, check img.bmp!\n", 28);
}
