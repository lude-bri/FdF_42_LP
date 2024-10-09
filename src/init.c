/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:24:18 by luigi             #+#    #+#             */
/*   Updated: 2024/10/09 19:29:59 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_win(t_mlx *win, t_map *map)
{
	win->mlx_connect = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx_connect, WIDTH, HEIGHT, "FdF");
	win->map = map;
	win->img.mlx_img = mlx_new_image(win->mlx_connect, WIDTH, HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.mlx_img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
}

void	init_hook(t_mlx *win)
{
	mlx_loop_hook(win->mlx_connect, &to_draw, win);
	mlx_key_hook(win->mlx_win, arrow_keys, win);
	mlx_hook(win->mlx_win, KeyPress, KeyPressMask, check_event, win);
	mlx_hook(win->mlx_win, 17, 0, to_close, win);
	mlx_loop(win->mlx_connect);
}

void	init_zoom(t_mlx *win, t_point *p1, t_point *p2)
{
	p1->x *= win->zoom;
	p1->y *= win->zoom;
	p1->z *= win->zoom;
	p1->z *= win->z_zoom;
	p2->x *= win->zoom;
	p2->y *= win->zoom;
	p2->z *= win->zoom;
	p2->z *= win->z_zoom;
}

void	init_map(t_map *map, int x, int y, t_z *z)
{
	map->w = x;
	map->h = y;
	z->z_max = 0;
	z->z_min = 0;
	map->coord = malloc(map->h * sizeof(t_point *));
}
