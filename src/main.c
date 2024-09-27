/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:11:51 by luigi             #+#    #+#             */
/*   Updated: 2024/09/27 12:47:48 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int ac, char **av)
{
	t_map	*map;
	char	*name;

	name = av[1];
	if (ac == 2)
	{
		if (sanity_check(name))
		{
			map = read_map(av[1]);
			render(map);
		}
		else
			ft_printf("Error: Wrong format\n");
	}
	if (ac > 2)
		ft_printf("Error: Too many arguments\n");
	else
		ft_printf("Error: Too few arguments\n");
	return (0);
}
