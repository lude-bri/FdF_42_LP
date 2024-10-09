/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:11:51 by luigi             #+#    #+#             */
/*   Updated: 2024/10/09 19:30:50 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int ac, char **av)
{
	t_map	*map;
	char	*name;
	int		fd;

	name = av[1];
	fd = 0;
	if (ac == 2)
	{
		if (sanity_check(name))
		{
			map = read_map(av[1], fd);
			fdf(map);
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

void	fdf(t_map *map)
{
	t_mlx	*win;

	win = malloc(sizeof(t_mlx));
	setup_window(win);
	init_win(win, map);
	init_hook(win);
}
