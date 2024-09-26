/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanity_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:15:30 by luigi             #+#    #+#             */
/*   Updated: 2024/09/26 12:24:21 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	sanity_check(char *name)
{
	int		len;
	int		c;
	int		i;
	char	*suffix;

	suffix = ".fdf";
	len = ft_strlen(name);
	if (len <= 3)
		return (0);
	len = len - 1;
	c = len - 3;
	i = 0;
	while (name[c])
	{
		if (name[c] != suffix[i])
			return (0);
		c++;
		i++;
	}
	return (1);
}
