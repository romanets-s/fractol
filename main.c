#include "fractol.h"

void	destroy(t_fr *f)
{
	mlx_destroy_image(f->mlx.mlx, f->mlx.img);
	mlx_clear_window(f->mlx.mlx, f->mlx.win);
	mlx_destroy_window(f->mlx.mlx, f->mlx.win);
	//freeall(f, -1);
	exit(0);
}


int		key_fun(int key, void *tmp)
{
	t_fr *f;

	f = (t_fr *)tmp;
	if (key == 53)
		destroy(f);
/*
	if (key == 91)
		rot_x(f->pix, 1);
	if (key == 84)
		rot_x(f->pix, -1);
	if (key == 86)
		rot_y(f->pix, 1);
	if (key == 88)
		rot_y(fdf->pix, -1);
	if (key == 89)
		rot_z(fdf->pix, 1);
	if (key == 92)
		rot_z(fdf->pix, -1);
	if (key == 69)
		zoom(fdf->pix, 1.2);
	if (key == 78)
		zoom(fdf->pix, 0.8);
	if (key == 67)
		change_color(fdf, -1);
	redraw(fdf);
*/
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

void	draw_pix(t_fr *f, int pix, int w, int c)
{
	f->mlx.str[pix + 0] = (unsigned char)(sin(f->rgb.red_frequency * f->rgb.index + f->rgb.red_phase) * w + c);
	f->mlx.str[pix + 1] = (unsigned char)(sin(f->rgb.grn_frequency * f->rgb.index + f->rgb.grn_phase) * w + c);
	f->mlx.str[pix + 2] = (unsigned char)(sin(f->rgb.blu_frequency * f->rgb.index + f->rgb.blu_phase) * w + c);
	f->mlx.str[pix + 3] = 0;
}

void	draw_color(t_fr *f, int pix, int i)
{
	f->rgb.index = i + 1 - (log(2) / sqrt(f->zx2 + f->zy2)) / log (2);
	if (i == f->i_max)
		draw_pix(f, pix, f->rgb.width1, f->rgb.center1);
	else
		draw_pix(f, pix, f->rgb.width2, f->rgb.center2);
}

void	mandelbrot(t_fr *f, int iy, int ix, int i)
{
	if (f->k != iy && (f->k = iy) >= 0)
	{
		f->cy = f->y_min + iy * f->pix_h;
		if (fabs(f->cy) < f->pix_h / 2)
			f->cy = 0.0;
	}
	f->cx = f->x_min + ix * f->pix_w;
	f->zx = 0.0;
	f->zy = 0.0;
	f->zx2 = f->zx * f->zx;
	f->zy2 = f->zy * f->zy;
	while (++i < f->i_max && ((f->zx2 + f->zy2) < f->er2))
	{
		f->zy = 2 * f->zx * f->zy + f->cy;
		f->zx = f->zx2 - f->zy2 + f->cx;
		f->zx2 = f->zx * f->zx;
		f->zy2 = f->zy * f->zy;
	}
	draw_color(f, iy * f->mlx.size_l + ix * 4, i);
}

void	julia(t_fr *f, int iy, int ix, int i)
{
	f->cx = -0.7;
	f->cy = 0.27015;

	f->zoom = 1;
	f->x_move = 0;
	f->y_move = 0;
	f->zx = 1.5 * (ix - MAX_W / 2) / (0.5 * f->zoom * MAX_W) + f->x_move;
	f->zy = (iy - MAX_H / 2) / (0.5 * f->zoom * MAX_H) + f->y_move;
	f->zx2 = f->zx * f->zx;
	f->zy2 = f->zy * f->zy;
	i = f->i_max;
	while (f->zx2 + f->zy2 < f->er2 && i--)
	{
		f->zx2 = f->zx * f->zx;
		f->zy2 = f->zy * f->zy;
		f->zy = 2 * f->zx * f->zy + f->cy;
		f->zx = f->zx2 - f->zy2 + f->cx;
	}
	f->zx2 = f->zx * f->zx;
	f->zy2 = f->zy * f->zy;
	draw_color(f, iy * f->mlx.size_l + ix * 4, i);
}

void	fractol(t_fr *f, int iy, int ix)
{
	f->k = -1;
	while (++iy < MAX_W)
	{
		ix = -1;
		while (++ix < MAX_H)
		{
			//mandelbrot(f, iy, ix, -1);
			julia(f, iy, ix, -1);
		}
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
	mlx_hook(f->mlx.win, 2, 5, &key_fun, f);
	mlx_loop(f->mlx.mlx);
}

void	init(t_fr *f, char *name)
{
	f->x_min = -2.5;
	f->x_max = 1.5;
	f->y_min = -2.0;
	f->y_max = 2.0;
	f->pix_w = (f->x_max - f->x_min) / MAX_H;
	f->pix_h = (f->y_max - f->y_min) / MAX_W;
	f->zx = 0.0;
	f->zy = 0.0;
	f->zx2 = f->zx * f->zx;
	f->zy2 = f->zy * f->zy;
	f->i_max = MAX_I;
	f->er = 2;
	f->er2 = f->er * f->er;
	f->name = name;
	f->rgb = init_color();


	f->mlx = create_mlx(f);

	fractol(f, -1, -1);
}

int		main(int c, char **v)
{
	int		i;
	t_fr	f[c - 1];

	i = 0;
	if (c > 1)
	{
		init(&f[i], v[i]);
		ft_putstr(v[i]);
		ft_putstr("\n");


			



	}
	else if (c > 4)
		ft_putstr("Many arguments, use max only 3\n");
	else
		ft_putstr("Usage: f1 or f2 or f3 or several together\n");
	return (0);
}
