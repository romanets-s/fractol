/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:39:38 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:39:39 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	key_hook_2(int key, t_fr *f)
{
	if (key == 78)
	{
		f->data.zoom += 0.02;
		f->data.i_max += 5;
	}
	else if (key == 69)
	{
		f->data.zoom -= 0.02;
		f->data.i_max += 5;
	}
}

static void	key_hook_1(int key, t_fr *f)
{
	if (key == 25)
		f->rgb.center1 += 1;
	else if (key == 31)
		f->rgb.center1 -= 1;
	else if (key == 29)
		f->rgb.center2 += 1;
	else if (key == 35)
		f->rgb.center2 -= 1;
	else if (key == 126 && f->fractal == 'm')
		f->data.x_move -= 0.1;
	else if (key == 124 && f->fractal == 'm')
		f->data.y_move += 0.1;
	else if (key == 125 && f->fractal == 'm')
		f->data.x_move += 0.1;
	else if (key == 123 && f->fractal == 'm')
		f->data.y_move -= 0.1;
	else if (key == 123 && f->fractal == 'j')
		f->data.x_move -= 0.1;
	else if (key == 125 && f->fractal == 'j')
		f->data.y_move += 0.1;
	else if (key == 124 && f->fractal == 'j')
		f->data.x_move += 0.1;
	else if (key == 126 && f->fractal == 'j')
		f->data.y_move -= 0.1;
	key_hook_2(key, f);
}

static void	key_hook_0(int key, t_fr *f)
{
	if (key == 20)
		f->rgb.blu_frequency += 0.001;
	else if (key == 14)
		f->rgb.blu_frequency -= 0.001;
	else if (key == 21)
		f->rgb.red_phase += 1;
	else if (key == 15)
		f->rgb.red_phase -= 1;
	else if (key == 23)
		f->rgb.grn_phase += 1;
	else if (key == 17)
		f->rgb.grn_phase -= 1;
	else if (key == 22)
		f->rgb.blu_phase += 1;
	else if (key == 16)
		f->rgb.blu_phase -= 1;
	else if (key == 26)
		f->rgb.width1 += 1;
	else if (key == 32)
		f->rgb.width1 -= 1;
	else if (key == 28)
		f->rgb.width2 += 1;
	else if (key == 34)
		f->rgb.width2 -= 1;
	key_hook_1(key, f);
}

int			key_hook(int key, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
	if (key == 53)
		destroy(f);
	if (key == 83 || key == 84 || key == 85)
	{
		change_fractal(f, key);
		return (1);
	}
	if (key == 49 && !f->mouse_res)
		f->mouse_res = 1;
	else if (key == 49 && f->mouse_res)
		f->mouse_res = 0;
	if (key == 18)
		f->rgb.red_frequency += 0.001;
	else if (key == 12)
		f->rgb.red_frequency -= 0.001;
	else if (key == 19)
		f->rgb.grn_frequency += 0.001;
	else if (key == 13)
		f->rgb.grn_frequency -= 0.001;
	key_hook_0(key, f);
	redraw(f);
	return (0);
}

int			key_hook_tree(int key, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
	if (key == 53)
		destroy(f);
	if (key == 83 || key == 84 || key == 85)
	{
		change_fractal(f, key);
		return (1);
	}
	else if (key == 124)
		f->tree.angle -= 1;
	else if (key == 123)
		f->tree.angle += 1;
	else if (key == 125 && f->tree.r)
		f->tree.r -= 1;
	else if (key == 126)
		f->tree.r += 1;
	else if (key == 78 && f->tree.depth)
		f->tree.depth -= 1;
	else if (key == 69 && f->tree.depth < 21)
		f->tree.depth += 1;
	redraw(f);
	return (0);
}
