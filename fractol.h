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

#include <stdio.h>

# define MAX_W 1200 // Y
# define MAX_H 1200 // X
# define MAX_I 200
# define MAX_THREADS 8

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				bpp;
	int				size_l;
	int				e;
	char			*str;
}					t_mlx;

typedef struct		s_color
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
}					t_color;

typedef struct		s_data
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
	double				x_move;
	double				y_move;
	struct s_fr		*f;
}					t_data;

typedef struct		s_fr
{

	char 			*name;
	struct s_data	data;
	struct s_color	rgb;
	struct s_mlx	mlx;

}					t_fr;


void	*fractol(void *arg);
void	speed(t_fr *f, int t, int i);



#endif
