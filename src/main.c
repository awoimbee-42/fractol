/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 18:39:03 by awoimbee          #+#    #+#             */
/*   Updated: 2018/11/30 19:26:15 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	msg_exit("Usage : ./fractol sale pute\n\
		\t-p precision: precision of rotation calculated as π/p, must be int\n\
		\t-c basecolor: color in capitalized hex w/ \"0x\" (default: FF0000)\n\
		\t-z zoom: dictate size of object, default to data->res.w / 2\n\
		\t-res width height: resolution of window, cannot be under 10", 0);
}

int		keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	keycode == K_LEW ? data->zoom /= 1.25 : 0;
	keycode == K_LES ? data->zoom *= 1.25 : 0;
	keycode == K_LFT ? data->pos.re -= data->zoom : 0;
	keycode == K_RGT ? data->pos.re += data->zoom : 0;
	keycode == K_AUP ? data->pos.im -= data->zoom : 0;
	keycode == K_DWN ? data->pos.im += data->zoom : 0;
	keycode == K_LER ? render_offscreen(data) : 0;
	keycode == K_PLS ? data->thickness *= 2 : 0;
	if (keycode == K_MNS)
		(data->thickness /= 2) < __DBL_MIN__ ?
		data->thickness = __DBL_MIN__ : 0;
	keycode == K_ESC ? exit(0) : 0;
	fprintf(stderr, "Key pressed : %d\n", keycode);
	render(data->mlx, data);
	return (1);
}

int		mouse_pos(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (x > 0 && x < data->res.w
	&& y > 0 && y < data->res.w)
	{
		data->mouse.im = (double)y / (double)data->res.h;
		data->mouse.re = (double)x / (double)data->res.w;
		render(data->mlx, data);
	}
	return (1);
}

void	read_args(t_data *data, char **argv, int argc)
{
	int		i;

	i = 1;
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
	mlx_hook(mlx.win, 2, 0, &keypress, &data);
	mlx_hook(mlx.win, 6, 1l << 6, &mouse_pos, &data);
	mlx_loop(mlx.ptr);
}
