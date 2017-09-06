/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:50:29 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:50:30 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, void *tmp)
{
	t_fr *f;

	x = y;
	f = (t_fr *)tmp;
	if (f->fractal == 't')
		return (0);
	if (button == 4)
	{
		f->data.zoom += 0.02;
		f->data.i_max += 1;
	}
	else if (button == 5)
	{
		f->data.zoom -= 0.02;
		f->data.i_max -= 1;
	}
	redraw(f);
	return (0);
}

int		mouse_exit(void *par)
{
	par = NULL;
	exit(1);
}

int		mouse_move(int x, int y, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
	if (x < 0 || y < 0 || x > MAX_W || y > MAX_H || f->mouse_res
		|| f->fractal != 'j')
		return (0);
	f->data.cx = ((double)x - MAX_W) / MAX_W;
	f->data.cy = ((double)y - MAX_H) / MAX_H;
	redraw(f);
	return (0);
}
