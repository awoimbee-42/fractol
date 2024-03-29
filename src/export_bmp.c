/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:53:25 by awoimbee          #+#    #+#             */
/*   Updated: 2018/12/13 01:56:37 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

/*
**	To better understand the code,
**		please look at the BMP file format specifications and headers
*/

void	export_bmp(t_env *data)
{
	FILE			*f;
	int				filesize;
	unsigned char	bmpfileheader[14];
	unsigned char	bmpinfoheader[40];

	filesize = data->res.w * data->res.h * 4 + 54;
	ft_memset(bmpfileheader, 0, 14);
	ft_memcpy(bmpfileheader, "BM", 2);
	ft_memcpy(&bmpfileheader[2], &filesize, 4);
	bmpfileheader[10] = 54;
	ft_memset(bmpinfoheader, 0, 40);
	bmpinfoheader[0] = 40;
	ft_memcpy(&bmpinfoheader[4], &data->res.w, 4);
	ft_memcpy(&bmpinfoheader[8], &data->res.h, 4);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = 32;
	f = fopen("img.bmp", "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	fwrite(data->mlx->img.px, data->res.w * data->res.h * 4, 1, f);
	fclose(f);
}
