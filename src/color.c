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

static void	colors_groups(t_point *point)
{
	int		colors[9][2];
	int		i;

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
	i = rand() % 9;
	point->icolor = colors[i][0];
	point->fcolor = colors[i][1];
}

void	to_colorize(t_point *point, int number_colors)
{
	int				i;
	float			f;
	unsigned char	rgb[3];

	colors_groups(point);
	f = 0;
	i = -1;
	while (++i < number_colors)
	{
		rgb[0] = get_color(point, f, get_r_c);
		rgb[1] = get_color(point, f, get_g_c);
		rgb[2] = get_color(point, f, get_b_c);
		f += (PI / 2) / (float)number_colors;
		point->color = ((int) rgb[0] << 16 | ((int)rgb[1]) << 8 | rgb[2]);
	}
}

unsigned char	get_color(t_point *point, float a, unsigned char (*f)(int))
{
	unsigned char	color;

	color = ft_min(f(point->icolor), f(point->fcolor))
		+ ((unsigned char)ft_abs(f(point->icolor) - f(point->fcolor)))
		* ((f(point->icolor) < f(point->fcolor)) * (sin(a))
			+ ((f(point->icolor) >= f(point->fcolor)) * cos(a)));
	return (color);
}

int	ft_min(int number1, int number2)
{
	if (number1 < number2)
		return (number1);
	else
		return (number2);
}
