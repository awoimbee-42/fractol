/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:39:03 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/02 20:17:13 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	msg_exit("Usage : ./fractol fractal_name [-res] [-c]\n\
		\t-c basecolor: color in capitalized hex w/ \"0x\" (default: 0000FF)\n\
		\t-z zoom: dictate size of object, default to 1\n\
		\t-res width height: resolution of window, cannot be under 10", 0);
}

void	read_args(t_data *data, char **argv, int argc)
{
	int		i;

	i = 1;
	if (ft_strcmp(argv[i], "mandelbrot") == 0)
		data->fract = &draw_mandel;
	else if (ft_strcmp(argv[i], "julia") == 0)
		data->fract = &draw_julia;
	else if (ft_strcmp(argv[i], "slow_julia") == 0)
		data->fract = &draw_slow_julia;
	else if (ft_strcmp(argv[i], "slow_mandelbrot") == 0)
		data->fract = &draw_slow_mandel;
	else
		usage();
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-res") == 0 && i + 2 < argc)
		{
			(data->res.w = ft_atoi(argv[++i])) < 10 ?
			msg_exit("Window width too small ! (%dpx)", &data->res.w) : 0;
			(data->res.h = ft_atoi(argv[++i])) < 10 ?
			msg_exit("Window height too small ! (%dpx)", &data->res.h) : 0;
		}
		else
			usage();
	}
}

void	init(t_data *data, t_mlx *mlx)
{
	chaos((mlx->ptr = mlx_init()));
	data->res.h = 700;
	data->res.w = 700;
	data->mlx = mlx;
	data->zoom = 1.;
	data->pos.im = 0;
	data->pos.im = 0;
	data->thickness = 0.01;
	data->fract = 0;
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_data	data;

	if (argc == 1 || argv[1][0] == '-')
		usage();
	init(&data, &mlx);
	read_args(&data, argv, argc);
	chaos((mlx.win = mlx_new_window(mlx.ptr,
		data.res.w, data.res.h, "Give good grade plz")));
	render(&mlx, &data);
	mlx_mouse_hook(mlx.win, &mouse_click, &data);
	mlx_hook(mlx.win, 2, 0, &keypress, &data);
	mlx_hook(mlx.win, 6, 1l << 6, &mouse_pos, &data);
	mlx_loop(mlx.ptr);
}
