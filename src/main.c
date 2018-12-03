/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:39:03 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/03 02:54:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	msg_exit("Usage : ./fractol fractal_name [-res] [-c]\n"
		"\tfractal_name can be [slow_]mandelbrot, [slow_]julia, burningship.\n"
		"\t-c basecolor: basecolor can be 1, 2 or 3 to draw Red, Gred or Blue\n"
		"\t-res width height: resolution of window, cannot be under 10", 0);
	return (0);
}

void		read_fract(void*(**fract)(void*), char *arg)
{
	if (ft_strcmp(arg, "mandelbrot") == 0)
		*fract = &draw_mandel;
	else if (ft_strcmp(arg, "julia") == 0)
		*fract = &draw_julia;
	else if (ft_strcmp(arg, "slow_julia") == 0)
		*fract = &draw_slow_julia;
	else if (ft_strcmp(arg, "slow_mandelbrot") == 0)
		*fract = &draw_slow_mandel;
	else if (ft_strcmp(arg, "burningship") == 0)
		*fract = &draw_burningship;
	else if (ft_strcmp(arg, "cosine_mandelbrot") == 0)
		*fract = &draw_cos_mandel;
	else if (ft_strcmp(arg, "cosine_julia") == 0)
		*fract = &draw_cos_julia;
	else
		usage();
}

void	read_args(t_data *data, char **argv, int argc)
{
	int		i;

	i = 1;
	read_fract(&data->fract, argv[i]);
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
	//mlx_hook(mlx.win, 2, 0, &keypress, &data);
	mlx_hook(mlx.win, 2, 1L << 0, &keypress, &data);
	mlx_hook(mlx.win, 6, 1L << 6, &mouse_pos, &data);
	mlx_loop(mlx.ptr);
}
