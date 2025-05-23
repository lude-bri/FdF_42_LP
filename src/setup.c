/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:26 by luigi             #+#    #+#             */
/*   Updated: 2024/10/09 19:31:35 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//this function setup the window for the start point of those variables
//in the beggining of the execution
void	setup_window(t_mlx *win)
{
	win->mlx_connect = 0;
	win->mlx_win = 0;
	win->map = 0;
	win->zoom = 10;
	win->z_zoom = 0.25;
	win->shift_x = 960;
	win->shift_y = 240;
	win->view = 0.70;
	win->c_factor = 1;
}

//this function verifies if there are colors announced in the map (ex: 0,0xFFFFFF)
//if this is the case, free (z), otherwhise, apply my colors.
void	setup_colors(t_map *map, t_z *z)
{
	if (check_color_true(map) == false)
		apply_color_grading(map, z);
	else
		free(z);
}
