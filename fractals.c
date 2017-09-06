/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:47:47 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:47:48 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_fr *f, t_data *d, int iy, int ix)
{
	int i;

	if (d->k != iy && (d->k = iy) >= 0)
	{
		d->cy = d->y_min + iy * d->pix_h;
		if (fabs(d->cy) < d->pix_h / 2)
			d->cy = 0.0;
	}
	d->cx = d->x_min + ix * d->pix_w;
	d->zx = 0.0;
	d->zy = 0.0;
	d->zx2 = d->zx * d->zx;
	d->zy2 = d->zy * d->zy;
	i = -1;
	while (++i < d->i_max && ((d->zx2 + d->zy2) < d->er2))
	{
		d->zy = (2 * d->zx * d->zy + d->cy * d->zoom) + d->x_move;
		d->zx = (d->zx2 - d->zy2 + d->cx * d->zoom) + d->y_move;
		d->zx2 = d->zx * d->zx;
		d->zy2 = d->zy * d->zy;
	}
	draw_color(f, d, iy * f->mlx.size_l + ix * 4, i);
}

void	julia(t_fr *f, t_data *d, int iy, int ix)
{
	int i;

	d->zx = 1.5 * (ix - MAX_W / 2) / (0.5 * MAX_W) * d->zoom + d->x_move;
	d->zy = (iy - MAX_H / 2) / (0.5 * MAX_H) * d->zoom + d->y_move;
	d->zx2 = d->zx * d->zx;
	d->zy2 = d->zy * d->zy;
	i = d->i_max;
	while (d->zx2 + d->zy2 < d->er2 && i--)
	{
		d->zx2 = d->zx * d->zx;
		d->zy2 = d->zy * d->zy;
		d->zy = 2 * d->zx * d->zy + d->cy;
		d->zx = d->zx2 - d->zy2 + d->cx;
	}
	d->zx2 = d->zx * d->zx;
	d->zy2 = d->zy * d->zy;
	draw_color(f, d, iy * f->mlx.size_l + ix * 4, i);
}

void	*fractol(void *arg)
{
	int		iy;
	int		ix;
	t_data	*d;

	d = (t_data *)arg;
	d->k = -1;
	iy = d->iy;
	while (++iy < d->max_w)
	{
		ix = -1;
		while (++ix < MAX_H)
		{
			if (d->f->fractal == 'm')
				mandelbrot(d->f, d, iy, ix);
			else if (d->f->fractal == 'j')
				julia(d->f, d, iy, ix);
		}
	}
	return (arg);
}

void	speed(t_fr *f, int t, int i)
{
	pthread_t	p[MAX_THREADS];
	t_data		tmp[MAX_THREADS];

	t = MAX_H / MAX_THREADS;
	while (++i < MAX_THREADS)
	{
		tmp[i] = copy_data(f, i * t - 1, i * t + t);
		pthread_create(&p[i], NULL, fractol, &tmp[i]);
	}
	i = -1;
	while (++i < MAX_THREADS)
		pthread_join(p[i], NULL);
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
	mlx_hook(f->mlx.win, 2, 5, &key_hook, f);
	mlx_mouse_hook(f->mlx.win, &mouse_hook, f);
	mlx_hook(f->mlx.win, 6, (1L << 6), mouse_move, f);
	mlx_hook(f->mlx.win, 17, (1L << 17), mouse_exit, f);
	mlx_loop(f->mlx.mlx);
}

void	tree(t_fr *f, t_tree *t, double angle, double depth)
{
	int		x0;
	int		y0;

	if (!depth)
		return ;
	t->x1 = t->x0 + (int)(cos(angle * 0.01745329252) * depth * t->r);
	t->y1 = t->y0 + (int)(sin(angle * 0.01745329252) * depth * t->r);
	line(f, t);
	t->x0 = t->x1;
	t->y0 = t->y1;
	x0 = t->x1;
	y0 = t->y1;
	tree(f, t, angle - 20, depth - 1);
	t->x0 = x0;
	t->y0 = y0;
	tree(f, t, angle + 20, depth - 1);
}
