/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:06:28 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 14:10:55 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//this function finds the ranges of z in the map (the z_max and z_min)
void	to_range_z(t_z *z, char **data)
{
	int		max;
	int		min;

	max = find_max(data);
	min = find_min(data);
	if (z->z_max < max)
		z->z_max = max;
	if (z->z_min > min)
		z->z_min = min;
}

//this function finds the max value of z
int	find_max(char **data)
{
	int		i;
	int		max;
	int		current_value;

	if (!data || !*data[0])
		return (0);
	i = 0;
	max = ft_atoi(data[0]);
	while (data[i])
	{
		current_value = ft_atoi(data[i]);
		if (current_value > max)
			max = current_value;
		i++;
	}
	return (max);
}

//this function finds the min value of z
int	find_min(char **data)
{
	int		i;
	int		min;
	int		current_value;

	i = 0;
	min = ft_atoi(data[0]);
	while (data[i])
	{
		current_value = ft_atoi(data[i]);
		if (current_value < min)
			min = current_value;
		i++;
	}
	return (min);
}
