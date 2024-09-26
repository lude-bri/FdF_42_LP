/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:49:27 by luigi             #+#    #+#             */
/*   Updated: 2024/09/26 11:15:00 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/wait.h>
# include <signal.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "../lib/mlx/mlx.h"

//This holds the values of watch point on the map
typedef struct	s_point
{
	float	x;
	float	y;
	int		z;
	int		color;
}			t_point;

//This will hold all the points of the map
typedef struct	s_map
{
	int		w;
	int		h;
	t_point	*coord;
}			t_map;

//This is needed for building the image
typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

//This will be our visual environment
typedef struct	s_mlx
{
	void	*mlx_connect;
	void	*mlx_win;
	t_map	*map;
	int		zoom;
	float	z_zoom;
	int		shift_x;
	int		shift_y;
	float	view;
	float	c_factor;
	t_img	img;
}			t_mlx;

#endif
