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
	f->mlx.str = mlx_get_data_addr(f->mlx.img, &f->mlx.bpp, &f->mlx.size_l, &f->mlx.e);
	speed(f, 0, -1);
}

t_color	init_color(void)
{
	t_color rgb;

	rgb.red_frequency = 0.016;
	rgb.grn_frequency = 0.013;
	rgb.blu_frequency = 0.01;
	rgb.red_phase = 4;
	rgb.grn_phase = 2;
	rgb.blu_phase = 1;
	rgb.width1 = 155;
	rgb.width2 = 230;
	rgb.center1 = 20;
	rgb.center2 = 25;
	rgb.index = 0;
	return (rgb);
}

int		key_hook(int key, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
	if (key == 53)
		destroy(f);
	printf("|%d|\n", key);
	if (key == 18)
		f->rgb.red_frequency += 0.001;
	else if (key == 12)
		f->rgb.red_frequency -= 0.001;
	else if (key == 19)
		f->rgb.grn_frequency += 0.001;
	else if (key == 13)
		f->rgb.grn_frequency -= 0.001;
	else if (key == 20)
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
	else if (key == 25)
		f->rgb.center1 += 1;
	else if (key == 31)
		f->rgb.center1 -= 1;
	else if (key == 29)
		f->rgb.center2 += 1;
	else if (key == 35)
		f->rgb.center2 -= 1;
	else if (key == 49)
		f->rgb = init_color();//return to fisrst arg
	else if (key == 126)
		f->data.x_move -= 0.1;
	else if (key == 124)
		f->data.y_move += 0.1;
	else if (key == 125)
		f->data.x_move += 0.1;
	else if (key == 123)
		f->data.y_move -= 0.1;
	else if (key == 78)
	{
		f->data.zoom += 0.02;
		f->data.i_max += 1;
	}
	else if (key == 69)
	{
		f->data.zoom -= 0.02;
		f->data.i_max += 1;
	}





	redraw(f);
	return (0);
}

t_mlx	create_mlx(t_fr *f)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, MAX_W, MAX_H, f->name);
	mlx.img = mlx_new_image(mlx.mlx, MAX_W, MAX_H);
	mlx.str = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_l, &mlx.e);
	return (mlx);
}

void	draw_color(t_fr *f, t_data *d, int pix, int i)
{
	d->rgb.index = i + 1 - (log(2) / sqrt(d->zx2 + d->zy2)) / log (2);
	if (i == d->i_max)
	{
		f->mlx.str[pix + 0] = (unsigned char)(sin(f->rgb.red_frequency
			* d->rgb.index + f->rgb.red_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 1] = (unsigned char)(sin(f->rgb.grn_frequency
			* d->rgb.index + f->rgb.grn_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 2] = (unsigned char)(sin(f->rgb.blu_frequency
			* d->rgb.index + f->rgb.blu_phase) * f->rgb.width1 + f->rgb.center1);
		f->mlx.str[pix + 3] = 0;
	}
	else
	{
		f->mlx.str[pix + 0] = (unsigned char)(sin(f->rgb.red_frequency
			* d->rgb.index + f->rgb.red_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 1] = (unsigned char)(sin(f->rgb.grn_frequency
			* d->rgb.index + f->rgb.grn_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 2] = (unsigned char)(sin(f->rgb.blu_frequency
			* d->rgb.index + f->rgb.blu_phase) * f->rgb.width2 + f->rgb.center2);
		f->mlx.str[pix + 3] = 0;
	}
}


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
		d->zx = (d->zx2 - d->zy2 + d->cx* d->zoom) + d->y_move;
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

int		mouse_hook(int button, int x, int y, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
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
	if (x < 0 || y < 0 || x > MAX_W || y > MAX_H)
		return (0);
	f->data.cx = ((double)x - MAX_W) / MAX_W;
	f->data.cy = ((double)y - MAX_H) / MAX_H;
	redraw(f);
	return (0);
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
			mandelbrot(d->f, d, iy, ix);
			//julia(d->f, d, iy, ix);
		}
	}
	return (arg);
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

void	init(t_fr *f, char *name)
{
	f->name = name;
	f->rgb = init_color();
	f->data = init_data();
	f->mlx = create_mlx(f);

// julia
	f->data.cx = -0.7;
	f->data.cy = 0.27015;

	
	speed(f, 0, -1);

}

int		main(int c, char **v)
{
	int		i;
	t_fr	f[c - 1];

	i = 0;
	if (c > 1)
	{
		init(&f[i], v[i]);
		// ft_putstr(v[i]);
		// ft_putstr("\n");
	}
	else if (c > 4)
		ft_putstr("Many arguments, use max only 3\n");
	else
		ft_putstr("Usage: f1 or f2 or f3 or several together\n");
	return (0);
}
