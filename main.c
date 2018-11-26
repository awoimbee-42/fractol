/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:25:55 by marvin            #+#    #+#             */
/*   Updated: 2018/11/26 22:25:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	msg_exit("Usage : ./fractol sale pute\n\
		\t-p precision: precision of rotation calculated as π/p, must be int\n\
		\t-c basecolor: color in capitalized hex w/ \"0x\" (default: FF0000)\n\
		\t-z zoom: dictate size of object, default to data->win_width / 2\n\
		\t-res width height: resolution of window, cannot be under 10", 0);
}

int		keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	keycode == K_LEW ? data->zoom *= 1.25 : 0;
	keycode == K_LES ? data->zoom /= 1.25 : 0;
	keycode == K_ESC ? exit(0) : 0;
	render(data->mlx, data);
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_data	data;

    chaos((mlx.ptr = mlx_init()));
	data.win_height = 700;
	data.win_width = 700;
	data.mlx = &mlx;
	data.zoom = 0;
	data.rgb = 0xFF0000;
	data.precisn = 8.;

    chaos((mlx.win = mlx_new_window(mlx.ptr,
		data.win_width, data.win_height, "Give good grade plz")));
	render(&mlx, &data);
	mlx_hook(mlx.win, 2, 0, &keypress, &data);
	mlx_loop(mlx.ptr);

}