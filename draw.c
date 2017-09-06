/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:51:32 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:51:34 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	destroy(t_fr *f)
{
	mlx_destroy_image(f->mlx.mlx, f->mlx.img);
	mlx_clear_window(f->mlx.mlx, f->mlx.win);
	mlx_destroy_window(f->mlx.mlx, f->mlx.win);
	exit(0);
}

void	redraw(t_fr *f)
{
	mlx_destroy_image(f->mlx.mlx, f->mlx.img);
	f->mlx.img = mlx_new_image(f->mlx.mlx, MAX_W, MAX_H);
	f->mlx.str = mlx_get_data_addr(f->mlx.img, &f->mlx.bpp,
		&f->mlx.size_l, &f->mlx.e);
	if (f->fractal == 't')
	{
		f->tree.x0 = MAX_W / 2;
		f->tree.y0 = MAX_H * 0.8;
		fractal_tree(f, &f->tree);
	}
	else if (f->fractal == 'j' || f->fractal == 'm')
		speed(f, 0, -1);
}

void	draw_color(t_fr *f, t_data *d, int pix, int i)
{
	d->rgb.index = i + 1 - (log(2) / sqrt(d->zx2 + d->zy2)) / log(2);
	if (i == d->i_max)
	{
		f->mlx.str[pix + 0] = (unsigned char)(sin(f->rgb.red_frequency *
			d->rgb.index + f->rgb.red_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 1] = (unsigned char)(sin(f->rgb.grn_frequency *
			d->rgb.index + f->rgb.grn_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 2] = (unsigned char)(sin(f->rgb.blu_frequency *
			d->rgb.index + f->rgb.blu_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 3] = 0;
	}
	else
	{
		f->mlx.str[pix + 0] = (unsigned char)(sin(f->rgb.red_frequency *
			d->rgb.index + f->rgb.red_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 1] = (unsigned char)(sin(f->rgb.grn_frequency *
			d->rgb.index + f->rgb.grn_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 2] = (unsigned char)(sin(f->rgb.blu_frequency *
			d->rgb.index + f->rgb.blu_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 3] = 0;
	}
}
