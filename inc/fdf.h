/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:49:27 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 13:58:22 by luigi            ###   ########.fr       */
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
# include <fcntl.h>
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

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265358979323846

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

//This holds the values of watch point on the map
typedef struct	s_point
{
	float	x;
	float	y;
	int		z;	//value found on (x,y)
	int		z_min;
	int		z_max;
	int		color;	//value found after "," if it doesnt have value, its white.
	int		icolor;
	int		fcolor;
}			t_point;

//This will hold all the points of the map
typedef struct	s_map
{
	int		w;
	int		h;
	t_point	**coord;
}			t_map;

//This is needed for building the image
typedef struct	s_img
{
	void	*mlx_img; //pointer to the image
	char	*addr; //image address
	int		bpp; //bits per pixel
	int		line_len; //line of image
	int		endian; //endian to adapt to the OS
}			t_img;

//This will be our visual environment
typedef struct	s_mlx
{
	void	*mlx_connect;  //pointer to mlx connection
	void	*mlx_win; //pointer to mlx window
	t_map	*map; //our map
	int		zoom; // bonus part ...
	float	z_zoom;
	int		shift_x;
	int		shift_y;
	float	view;
	float	c_factor;
	int		c_index;
	t_img	img; //our image
}			t_mlx;

typedef struct  s_z
{
	int		z_min;
	int		z_max;
}			t_z;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

//main.c

//parser.c
int		get_dimensions(int *x, int *y, char *file);
t_map	*read_map(char *filemap);
void	fill_mtrx(t_point *row, char *line, int y, t_z *z);
void	set_point(t_point *point, char *str, int x, int y);

//free_and_exit.c
void	error_clean(int fd, char *str);
void	free_args(char **numbers);
void	free_map(t_map *map);
void	clean_and_exit(t_mlx *mlx);
int		to_close(t_mlx *mlx);

//sanity_check.c
int	sanity_check(char *name);

//setup.c
void	setup_window(t_mlx *win);
int		rgb_to_int(char *color);
void	init_zoom(t_mlx *win, t_point *p1, t_point *p2);
int		ft_max(int number1, int number2);
int		ft_mod(int n);

//render.c
void	isometric_view(t_point *p, float ang);
void	bresenham(t_mlx *win, t_point p1, t_point p2);
int		to_draw(t_mlx *win);
void	render(t_map *map);
void	render_bg(t_img *img, int color);

//display.c
void	pixel_put(t_img *img, int x, int y, int color);
void	display(t_mlx *win);
void	display_map(t_map *map);

//hooks.c
int		check_event(int Key, t_mlx * mlx);
int		arrow_keys(int Key, t_mlx *mlx);
int		more_keys(int Key, t_mlx *mlx);
void	ft_reset(t_mlx *win);

//color.c
//void	to_colorize(t_point *point, int number_colors);
int		ft_min(int number1, int number2);
void	to_colorize(t_point *point, float normalized_z);
unsigned char	get_color(t_point *point, float a, unsigned char (*f)(int));
void	apply_color_grading(t_map *map, t_z *z);

//rgb.c
unsigned char	get_t_c(int trgb);
unsigned char	get_r_c(int trgb);
unsigned char	get_g_c(int trgb);
unsigned char	get_b_c(int trgb);

//range.c
void	range_z(t_point *point);

#endif
