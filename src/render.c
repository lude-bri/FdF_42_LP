/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:33:34 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 13:52:06 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	isometric_view(t_point *p, float ang)
{
	p->x = (p->x - p->y) * cos(ang); //Rotate x and y coordinates
	p->y = (p->x + p->y) * sin(ang) - p->z; //Adjust y coordinate and subtr z for depth
}

void	bresenham(t_mlx *win, t_point p1, t_point p2)
{
	float	x_step;
	float	y_step;
	int		max;

	//Adjust some point based on zoom level
	init_zoom(win, &p1, &p2);
	//Apply isometric view if it's not applied
	if (win->view != 3)
	{
		isometric_view(&p1, win->view);
		isometric_view(&p2, win->view);
	}
	//Apply shift offsets for positioning
	p1.x += win->shift_x;
	p1.y += win->shift_y;
	p2.x += win->shift_x;
	p2.y += win->shift_y;

	// Calculate step sizes for incremental drawing
	x_step = p2.x - p1.x;
	y_step = p2.y - p1.y;

	max = ft_max(ft_mod(x_step), ft_mod(y_step));
	x_step /= max;
	y_step /= max;

	while ((int)(p1.x - p2.x) || (int)(p1.y - p2.y))
	{
		pixel_put(&win->img, p1.x, p1.y, p1.color * win->c_factor);
		p1.x += x_step;
		p1.y += y_step;
	}
}

int	to_draw(t_mlx *win)
{
	int		y;
	int		x;

	//posso fazer um set_color aqui
	render_bg(&win->img, 0x000000);
	y = 0;
	while (y < win->map->h)
	{
		x = 0;
		while (x < win->map->w)
		{
			if (x < win->map->w - 1)
				bresenham(win, win->map->coord[y][x], win->map->coord[y][x + 1]);
			if (y < win->map->h - 1)
				bresenham(win, win->map->coord[y][x], win->map->coord[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx_connect, win->mlx_win, win->img.mlx_img, 0, 0);
	display(win);
	return (0);
}

void	render(t_map *map)
{
	t_mlx	*win;

	win = malloc(sizeof(t_mlx));
	setup_window(win);
	win->mlx_connect = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx_connect, WIDTH, HEIGHT, "FdF");
	win->map = map;
	win->img.mlx_img = mlx_new_image(win->mlx_connect, WIDTH, HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.mlx_img, &win->img.bpp, 
					&win->img.line_len, &win->img.endian);
	mlx_loop_hook(win->mlx_connect, &to_draw, win);
	mlx_key_hook(win->mlx_win, arrow_keys, win);
	mlx_hook(win->mlx_win, KeyPress, KeyPressMask, check_event, win);
	mlx_hook(win->mlx_win, 17, 0, to_close, win);
	mlx_loop(win->mlx_connect);
}

void	render_bg(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			pixel_put(img, x++, y, color);
		++y;
	}
}
