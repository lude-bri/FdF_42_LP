/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:49:27 by luigi             #+#    #+#             */
/*   Updated: 2024/09/26 12:40:54 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

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
# include "../lib/libft/libft_42/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

//main.c

//parser.c
int	get_dimensions(int *x, int *y, char *file);
t_map *read_map(char *filemap);
void	fill_mtrx(t_point *row, char *line, int y);
void	set_point(t_point *point, char *str, int x, int y);

//free_and_exit.c
void	error_clean(int fd, char *str);
void	free_args(char **numbers);

//sanity_check.c
int	sanity_check(char *name);

//setup.c
int	rgb_to_int(char *color);

#endif
