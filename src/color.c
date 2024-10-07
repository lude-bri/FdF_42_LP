/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:55:25 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 13:52:46 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static unsigned char interpolate_color(int icolor, int fcolor, float factor, unsigned char (*get_component)(int));

void	apply_color_grading(t_map *map, t_z *z)
{
	int y = 0;
	int x;
	int range;

	// Calculate the Z range
	range = ft_abs(z->z_max - z->z_min);

	// If there's no range, the map is flat, so no need to colorize
	if (range == 0)
		return;

	// Iterate through all points in the map
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			// Normalize the Z value of the point (0 to 1)
			float normalized_z = (float)(map->coord[y][x].z - z->z_min) / range;
			
			// Pass the normalized Z value to `to_colorize`
			to_colorize(&map->coord[y][x], normalized_z);
			x++;
		}
		y++;
	}
	free(z);
}

static void	colors_groups(t_point *point)
{
	int		colors[9][2];
	int		i = 1;

	colors[0][0] = 0x20002C;
	colors[0][1] = 0xCBB4D4;
	colors[1][0] = 0x34E89E;
	colors[1][1] = 0x0F3443;
	colors[2][0] = 0x0575E6;
	colors[2][1] = 0x021B79;
	colors[3][0] = 0x43C6AC;
	colors[3][1] = 0x191654;
	colors[4][0] = 0x43c6ac;
	colors[4][1] = 0xf8ffae;
	colors[5][0] = 0xC0C0AA;
	colors[5][1] = 0x1CEFFF;
	colors[6][0] = 0xDBE6F6;
	colors[6][1] = 0xC5796D;
	colors[7][0] = 0x868F96;
	colors[7][1] = 0x596164;
	colors[8][0] = 0x30E8BF;
	colors[8][1] = 0xFF8235;
	//i = rand() % 9;
	point->icolor = colors[i][0];
	point->fcolor = colors[i][1];
}

void	to_colorize(t_point *point, float normalized_z)
{
	unsigned char rgb[3];

	// Ensure colors_groups assigns the base colors
	colors_groups(point);

	// Interpolate between the base colors based on normalized Z value (0 to 1)
	rgb[0] = interpolate_color(point->icolor, point->fcolor, normalized_z, get_r_c);  // Red channel
	rgb[1] = interpolate_color(point->icolor, point->fcolor, normalized_z, get_g_c);  // Green channel
	rgb[2] = interpolate_color(point->icolor, point->fcolor, normalized_z, get_b_c);  // Blue channel

	// Combine RGB components into a single color
	point->color = ((int)rgb[0] << 16 | (int)rgb[1] << 8 | rgb[2]);
}

static unsigned char interpolate_color(int icolor, int fcolor, float factor, unsigned char (*get_component)(int))
{
	unsigned char start = get_component(icolor);  // Starting color component
	unsigned char end = get_component(fcolor);    // Ending color component

	// Linear interpolation between start and end based on factor (normalized_z)
	return (unsigned char)(start + (end - start) * factor);
}

int	ft_min(int number1, int number2)
{
	if (number1 < number2)
		return (number1);
	else
		return (number2);
}
