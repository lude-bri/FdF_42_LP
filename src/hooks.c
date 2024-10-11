/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:13:37 by luigi             #+#    #+#             */
/*   Updated: 2024/10/09 19:31:54 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//this function deals the exit key to clean and exit the window
int	check_event(int Key, t_mlx *mlx)
{
	if (Key == XK_Escape)
		clean_and_exit(mlx);
	return (0);
}

//this function deals with keys in keyboard
int	arrow_keys(int Key, t_mlx *mlx)
{
	if (Key == XK_Right)
		mlx->shift_x += 10;
	if (Key == XK_Left)
		mlx->shift_x -= 10;
	if (Key == XK_Up)
		mlx->shift_y -= 10;
	if (Key == XK_Down)
		mlx->shift_y += 10;
	if (Key == XK_equal)
		mlx->zoom += 1;
	if (Key == XK_minus && mlx->zoom >= 2)
		mlx->zoom -= 1;
	if (Key == XK_r)
		reset_map(mlx);
	more_keys(Key, mlx);
	return (0);
}

//this function is aux to arrow_keys
int	more_keys(int Key, t_mlx *mlx)
{
	if (Key == XK_1)
		mlx->view = 0.78;
	if (Key == XK_2)
		mlx->view = 0;
	if (Key == XK_3)
		mlx->view = 3;
	if (Key == XK_c)
		mlx->c_factor += 510;
	if (Key == XK_d)
		mlx->view += 0.1;
	return (0);
}

//this function reset the map to the setup config
void	reset_map(t_mlx *win)
{
	win->zoom = 10;
	win->z_zoom = 0.25;
	win->shift_x = 960;
	win->shift_y = 240;
	win->view = 0.70;
	win->c_factor = 1;
}
