/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:51:16 by luigi             #+#    #+#             */
/*   Updated: 2024/10/08 19:51:51 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//this function transforms rgb to int
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

//this function finds the max number in between two numbers
int	ft_max(int number1, int number2)
{
	int	n;

	n = number1 - number2;
	if (n > 0)
		return (number1);
	else
		return (number2);
}

//this function finds the mod of a number
int	ft_mod(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}
