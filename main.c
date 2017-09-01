#include "fractol.h"

t_mlx	create_mlx(t_fr *f)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, MAX_W, MAX_H, f->name);
	mlx.img = mlx_new_image(mlx.mlx, MAX_W, MAX_H);
	mlx.str = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_l, &mlx.e);
	return (mlx);
}

void	mandelbrot(t_fr *f, int iy, int ix, int i)
{
	double cx;
	double cy;

	while (++iy < MAX_W)
	{
		cy = f->y_min + iy * f->pix_h;
		if (fabs(cy) < f->pix_h / 2)
			cy = 0.0;
		while (++ix < MAX_H)
		{
			cx = f->x_min + ix * f->pix_w;
			f->zx = 0;
			f->zy = 0;
			f->zx2 = f->zx * f->zx;
			f->zy2 = f->zy * f->zy;
			while (++i < f->i_max && ((f->zx2 + f->zy2) < f->er2))
			{
				f->zy = 2 * f->zx * f->zy + cy;
				f->zx = f->zx2 - f->zy2 + cx;
				f->zx2 = f->zx * f->zx;
				f->zy2 = f->zy * f->zy;
			}
			if (i == f->i_max)
			{

			}
			else
			{

			}
		}
	}
}

void	init(t_fr *f, char *name)
{
	f->x_min = 2.5;
	f->x_max = 1.5;
	f->y_min = 2.0;
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


	f->mlx = create_mlx(f);
	mandelbrot(f, -1, -1, -1);
}

int		main(int c, char **v)
{
	int		i;
	t_fr	f[c - 1];

	i = 0;
	if (c > 1)
	{

		while (c > ++i)
		{
			init(&f[i], v[i]);

			ft_putstr(v[i]);
			ft_putstr("\n");
		}
	}
	else if (c > 4)
		ft_putstr("Many arguments, use max only 3\n");
	else
		ft_putstr("Usage: f1 or f2 or f3 or several together\n");
	return (0);
}
