/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sromanet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 22:05:41 by sromanet          #+#    #+#             */
/*   Updated: 2017/08/28 22:05:46 by sromanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# define MAX_W 1000
# define MAX_H 1000
# define MAX_I 100
# define MAX_THREADS 8

typedef struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				bpp;
	int				size_l;
	int				e;
	char			*str;
}				t_mlx;

typedef struct	s_color
{
	double			red_frequency;
	double			grn_frequency;
	double			blu_frequency;
	int				red_phase;
	int				grn_phase;
	int				blu_phase;
	int				width1;
	int				width2;
	int				center1;
	int				center2;
	double			index;
}				t_color;

typedef struct	s_tree
{
	double			angle;
	double			depth;
	double			r;
	int				x;
	int				y;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				lengthx;
	int				lengthy;
	int				d;
	unsigned char	color[3];
}				t_tree;

typedef struct	s_data
{
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	double			pix_w;
	double			pix_h;
	double			zx;
	double			zy;
	double			zx2;
	double			zy2;
	double			cx;
	double			cy;
	int				i_max;
	double			er;
	double			er2;
	int				k;
	struct s_color	rgb;
	int				iy;
	int				max_w;
	double			zoom;
	double			x_move;
	double			y_move;
	struct s_fr		*f;
}				t_data;

typedef struct	s_fr
{
	char			fractal;
	char			*name;
	int				mouse_res;
	struct s_tree	tree;
	struct s_data	data;
	struct s_color	rgb;
	struct s_mlx	mlx;
}				t_fr;

t_color			init_color(void);
t_tree			init_data_tree(void);
t_data			init_data(void);
t_data			copy_data(t_fr *f, int iy, int max_w);
int				key_hook_tree(int key, void *tmp);
int				key_hook(int key, void *tmp);
int				mouse_hook(int button, int x, int y, void *tmp);
int				mouse_exit(void *par);
int				mouse_move(int x, int y, void *tmp);
int				ft_dif(int p1, int p2);
void			line_x(t_fr *f, t_tree *t, int l, int n);
void			line_y(t_fr *f, t_tree *t, int l, int n);
void			line(t_fr *f, t_tree *t);
void			fractal_tree(t_fr *f, t_tree *t);
void			mandelbrot(t_fr *f, t_data *d, int iy, int ix);
void			julia(t_fr *f, t_data *d, int iy, int ix);
void			*fractol(void *arg);
void			speed(t_fr *f, int t, int i);
void			tree(t_fr *f, t_tree *t, double angle, double depth);
int				mouse_hook(int button, int x, int y, void *tmp);
int				mouse_exit(void *par);
int				mouse_move(int x, int y, void *tmp);
void			destroy(t_fr *f);
void			redraw(t_fr *f);
void			draw_color(t_fr *f, t_data *d, int pix, int i);
t_mlx			create_mlx(t_fr *f);
void			change_fractal(t_fr *f, int key);
char			*fractal_name(char c);
void			init(t_fr *f, char *name);

#endif
