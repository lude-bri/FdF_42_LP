/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:24:26 by luigi             #+#    #+#             */
/*   Updated: 2024/09/26 12:38:22 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	rgb_to_int(char *color)
{
	int		c;
	int		result;

	result = 0;
	c = 2;
	while(ft_isdigit(color[c]) || (color[c] >= 'a' && color[c] <= 'f') ||
	   (color[c] >= 'A' && color[c] <= 'F'))
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
