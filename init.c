/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:38:37 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:38:39 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	init_color(void)
{
	t_color rgb;

	rgb.red_frequency = 0.072;
	rgb.grn_frequency = 0.016;
	rgb.blu_frequency = 0.022;
	rgb.red_phase = -4;
	rgb.grn_phase = 7;
	rgb.blu_phase = 2;
	rgb.width1 = 156;
	rgb.width2 = 230;
	rgb.center1 = 20;
	rgb.center2 = 25;
	rgb.index = 0;
	return (rgb);
}

t_tree	init_data_tree(void)
{
	t_tree	t;

	t.angle = -90;
	t.depth = 10;
	t.r = 10.0;
	t.x = 0;
	t.y = 0;
	t.x0 = MAX_W / 2;
	t.x1 = 0;
	t.y0 = MAX_H * 0.8;
	t.y1 = 0;
	t.lengthx = 0;
	t.lengthy = 0;
	t.d = 0;
	t.color[0] = 0;
	t.color[1] = 255;
	t.color[2] = 0;
	return (t);
}

t_data	init_data(void)
{
	t_data	data;

	data.x_min = -2.5;
	data.x_max = 1.5;
	data.y_min = -2.0;
	data.y_max = 2.0;
	data.pix_w = (data.x_max - data.x_min) / MAX_H;
	data.pix_h = (data.y_max - data.y_min) / MAX_W;
	data.zx = 0.0;
	data.zy = 0.0;
	data.zx2 = 0.0;
	data.zy2 = 0.0;
	data.i_max = MAX_I;
	data.er = 2;
	data.er2 = data.er * data.er;
	data.zoom = 1;
	data.x_move = 0;
	data.y_move = 0;
	data.rgb = init_color();
	data.cx = -0.7;
	data.cy = 0.27015;
	return (data);
}

t_data	copy_data(t_fr *f, int iy, int max_w)
{
	t_data data;

	data.x_min = f->data.x_min;
	data.x_max = f->data.x_max;
	data.y_min = f->data.y_min;
	data.y_max = f->data.y_max;
	data.pix_w = f->data.pix_w;
	data.pix_h = f->data.pix_h;
	data.zx = f->data.zx;
	data.zy = f->data.zy;
	data.zx2 = f->data.zx2;
	data.zy2 = f->data.zy2;
	data.cx = f->data.cx;
	data.cy = f->data.cy;
	data.i_max = f->data.i_max;
	data.er = f->data.er;
	data.er2 = f->data.er2;
	data.iy = iy;
	data.max_w = max_w;
	data.zoom = f->data.zoom;
	data.x_move = f->data.x_move;
	data.y_move = f->data.y_move;
	data.rgb = f->rgb;
	data.f = f;
	return (data);
}
