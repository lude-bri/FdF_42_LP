/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:26 by luigi             #+#    #+#             */
/*   Updated: 2024/09/27 12:31:24 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	setup_window(t_mlx *win)
{
	win->mlx_connect = 0;
	win->mlx_win = 0;
	win->map = 0;
	win->zoom = 10;
	win->z_zoom = 0.25;
	win->shift_x = 960;
	win->shift_y = 240; 
	win->view = 0.78;
	win->c_factor = 1;
}

int	rgb_to_int(char *color)
{
	int		c;
	int		result;

	result = 0;
	c = 2;
	while (ft_isdigit(color[c]) || (color[c] >= 'a' && color[c] <= 'f')
		|| (color[c] >= 'A' && color[c] <= 'F'))
	{
		result = result * 16;
		if (color[c] <= 9)
			result = result + color[c] - '0';
		else if (color[c] >= 'a' && color[c] <= 'f')
			result = result + color[c] - 'a' + 10;
		else
			result = result + color[c] - 'A' + 10;
		c++;
	}
	return (result);
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

int	ft_max(int number1, int number2)
{
	int	n;

	n = number1 - number2;
	if (n > 0)
		return (number1);
	else
		return (number2);
}

int	ft_mod(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}
