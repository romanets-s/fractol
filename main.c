/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:54:15 by sromanet          #+#    #+#             */
/*   Updated: 2017/09/06 15:54:17 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	change_fractal(t_fr *f, int key)
{
	if (key == 83)
		f->fractal = 'm';
	else if (key == 84)
		f->fractal = 'j';
	else if (key == 85)
		f->fractal = 't';
	f->data = init_data();
	f->tree = init_data_tree();
	redraw(f);
}

char	*fractal_name(char c)
{
	if (c == 'm')
		return ("Fractal \"Mandelbrot\"");
	else if (c == 'j')
		return ("Fractal \"Julia\"");
	else if (c == 't')
		return ("Fractal \"Tree\"");
	return (NULL);
}

void	init(t_fr *f, char *name)
{
	if (!ft_strequ("t", name) && !ft_strequ("m", name) && !ft_strequ("j", name))
	{
		ft_putstr(name);
		ft_putstr(" - Wrong fractal shortcut\n");
		return ;
	}
	f->fractal = name[0];
	f->name = fractal_name(f->fractal);
	f->rgb = init_color();
	f->data = init_data();
	f->mlx = create_mlx(f);
	f->tree = init_data_tree();
	if (f->fractal == 'm' || f->fractal == 'j')
		speed(f, 0, -1);
	else if (f->fractal == 't')
		fractal_tree(f, &f->tree);
}

int		main(int c, char **v)
{
	int		i;
	t_fr	f[c - 1];
	pid_t	id;

	if (c > 1 && c < 5)
	{
		i = 0;
		while (i + 1 < c)
		{
			id = fork();
			if (id == 0)
				i += 1;
			else
			{
				init(&f[i], v[i + 1]);
				break ;
			}
		}
	}
	else if (c > 4)
		ft_putstr("Many arguments, use max 3\n");
	else
		ft_putstr("Usage: m or j or t or several together\n");
	return (0);
}
