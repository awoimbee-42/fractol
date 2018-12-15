/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:39:03 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/15 01:40:02 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	msg_exit("Usage : ./fractol fractal_name [-res]\n"
		"\tfractal_name can be [slow_]mandelbrot, [slow_]julia,"
		" cosine_mandelbrot, burningship.\n"
		"\t-res width height: resolution of window, cannot be under 10\n"
		"\t\t(default is 700x700)\n", 0);
	return (0);
}

void	read_fract(void *(**fract)(void*), char *arg)
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
	else
		usage();
}

void	read_args(t_env *data, char **argv, int argc)
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

void	init(t_env *data, t_mlx *mlx)
{
	int		i;

	chaos((mlx->ptr = mlx_init()));
	data->res.h = 700;
	data->res.w = 700;
	data->mlx = mlx;
	data->iter_max = 50;
	data->zoom = 1.;
	data->pos.re = 0;
	data->pos.im = 0;
	data->fract = 0;
	i = -1;
	while (++i < THREADS_NB)
	{
		data->threads[i].env = data;
		data->threads[i].line_start = (i * data->res.h) / THREADS_NB;
		data->threads[i].line_end = (((i + 1) * data->res.h) / THREADS_NB) + 1;
	}
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_env	data;

	if (argc == 1 || argv[1][0] == '-')
		usage();
	init(&data, &mlx);
	read_args(&data, argv, argc);
	chaos((mlx.win = mlx_new_window(mlx.ptr,
		data.res.w, data.res.h, "Give good grade plz")));
	print_instructions();
	mlx_mouse_hook(mlx.win, &mouse_click, &data);
	mlx_hook(mlx.win, 2, 1L << 0, &keypress, &data);
	mlx_hook(mlx.win, 6, 1L << 6, &mouse_pos, &data);
	render(&mlx, &data);
	mlx_loop(mlx.ptr);
}
