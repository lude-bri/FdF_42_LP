/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:26 by luigi             #+#    #+#             */
/*   Updated: 2024/10/08 19:57:57 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	setup_window(t_mlx *win)
{
	win->mlx_connect = 0;
	win->mlx_win = 0;
	win->map = 0;
	win->zoom = 30;
	win->z_zoom = 0.25;
	win->shift_x = 960;
	win->shift_y = 240;
	win->view = 0.70;
	win->c_factor = 1;
}

void	setup_colors(t_map *map, t_z *z)
{
	if (check_color_true(map) == false)
		apply_color_grading(map, z);
	else
		free(z);
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
