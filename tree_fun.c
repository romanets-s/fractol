/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:43:34 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:43:36 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_dif(int p1, int p2)
{
	if (p2 - p1 >= 0)
		return (1);
	else
		return (-1);
}

void	line_x(t_fr *f, t_tree *t, int l, int n)
{
	int q;

	while (l--)
	{
		q = t->x * 4;
		n = t->y * f->mlx.size_l + q;
		if (n >= 0 && n < f->mlx.size_l * MAX_W && q >= 0 && q < f->mlx.size_l)
		{
			f->mlx.str[n + 0] = t->color[0];
			f->mlx.str[n + 1] = t->color[1];
			f->mlx.str[n + 2] = t->color[2];
		}
		t->x += ft_dif(t->x0, t->x1);
		t->d += 2 * t->lengthy;
		if (t->d > 0)
		{
			t->d -= 2 * t->lengthx;
			t->y += ft_dif(t->y0, t->y1);
		}
	}
}

void	line_y(t_fr *f, t_tree *t, int l, int n)
{
	int q;

	while (l--)
	{
		q = t->x * 4;
		n = t->y * f->mlx.size_l + q;
		if (n >= 0 && n < f->mlx.size_l * MAX_W && q >= 0 && q < f->mlx.size_l)
		{
			f->mlx.str[n + 0] = t->color[0];
			f->mlx.str[n + 1] = t->color[1];
			f->mlx.str[n + 2] = t->color[2];
		}
		t->y += ft_dif(t->y0, t->y1);
		t->d += 2 * t->lengthx;
		if (t->d > 0)
		{
			t->d -= 2 * t->lengthy;
			t->x += ft_dif(t->x0, t->x1);
		}
	}
}

void	line(t_fr *f, t_tree *t)
{
	int		l;

	t->lengthx = abs(t->x1 - t->x0);
	t->lengthy = abs(t->y1 - t->y0);
	if (t->lengthx > t->lengthy)
		l = t->lengthx + 1;
	else
		l = t->lengthy + 1;
	t->x = t->x0;
	t->y = t->y0;
	if (t->lengthx >= t->lengthy)
	{
		t->d = -t->lengthx;
		line_x(f, t, l, 0);
	}
	else
	{
		t->d = -t->lengthy;
		line_y(f, t, l, 0);
	}
}

void	fractal_tree(t_fr *f, t_tree *t)
{
	tree(f, t, t->angle, t->depth);
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
	mlx_hook(f->mlx.win, 2, 5, &key_hook_tree, f);
	mlx_hook(f->mlx.win, 17, (1L << 17), mouse_exit, f);
	mlx_loop(f->mlx.mlx);
}
