/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:18:51 by luigi             #+#    #+#             */
/*   Updated: 2024/09/27 12:53:04 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

void	display(t_mlx *win)
{
	mlx_string_put(win->mlx_connect, win->mlx_win, 1820, 20, -1,
				"By lude-bri");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 20, -1,
				"Use arrow key to move");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 40, -1,
				"Use - or + for zoom");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 60, -1,
				"Use z or x to level Z axys");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 80, -1,
				"Press 1, 2 or 3 to change views");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 100, -1,
				"Press c to change colors");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 120, -1,
				"Press r to reset");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 140, -1,
				"Press d to see a neat rotation");
	mlx_string_put(win->mlx_connect, win->mlx_win, 35, 160, -1,
				"Press ESC or the X icon to exit");
}

void	display_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->h > y)
	{
		while (map->w > x)
		{
			ft_printf("%i ", map->coord[y][x].z);
			x++;
		}
		ft_printf("\n");
		x = 0;
		y++;
	}
}
