/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:39:03 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/12 02:30:34 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		usage(void)
{
	ft_fprintf(2,
		"<bold>Usage : ./fractol fractal_name [-res]</bold>\n"
		"\tfractal_name can be:\n"
		"\t\tmandelbrot, julia, basic_mandelbrot, basic_julia,\n"
		"\t\tcosine, burningship, koch.\n"
		"\t-res width height:\n"
		"\t\tresolution of window, cannot be under 10 (default is 700x700)\n");
	exit(EXIT_FAILURE);
	return (0);
}

void	read_fract(void *(**fract)(void*), char *arg)
{
	if (ft_strcmp(arg, "mandelbrot") == 0)
		*fract = &draw_mandel;
	else if (ft_strcmp(arg, "julia") == 0)
		*fract = &draw_julia;
	else if (ft_strcmp(arg, "basic_julia") == 0)
		*fract = &draw_slow_julia;
	else if (ft_strcmp(arg, "basic_mandelbrot") == 0)
		*fract = &draw_slow_mandel;
	else if (ft_strcmp(arg, "burningship") == 0)
		*fract = &draw_burningship;
	else if (ft_strcmp(arg, "cosine") == 0)
		*fract = &draw_cos_mandel;
	else if (ft_strcmp(arg, "koch") == 0)
		*fract = &draw_koch;
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
	chaos((mlx->ptr = mlx_init()));
	data->res = (t_res){700, 700};
	data->mlx = mlx;
	data->iter_max = 50;
	data->zoom = 1.;
	data->pos = (t_complex){0, 0};
	data->fract = 0;
	data->mouse = (t_complex){1, 0};
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_env	data;
	int		i;

	if (argc == 1 || argv[1][0] == '-')
		usage();
	init(&data, &mlx);
	read_args(&data, argv, argc);
	i = -1;
	while (++i < THREADS_NB)
	{
		data.threads[i].env = &data;
		data.threads[i].line_start = (i * data.res.h) / THREADS_NB;
		data.threads[i].line_end = (((i + 1) * data.res.h) / THREADS_NB) + 1;
	}
	chaos((mlx.win = mlx_new_window(mlx.ptr,
		data.res.w, data.res.h, "Give good grade plz")));
	print_instructions();
	mlx_mouse_hook(mlx.win, &mouse_click, &data);
	mlx_hook(mlx.win, 2, 1L << 0, &keypress, &data);
	mlx_hook(mlx.win, 6, 1L << 6, &mouse_pos, &data);
	mlx_hook(mlx.win, 17, 0, set_close, &data);
	mlx_loop_hook(mlx.ptr, loop, &data);
	render(&mlx, &data);
	mlx_loop(mlx.ptr);
}
