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
	win->mlx_connect = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx_connect, WIDTH, HEIGHT, "FdF");
	win->map = map;
	win->img.mlx_img = mlx_new_image(win->mlx_connect, WIDTH, HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.mlx_img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	mlx_loop_hook(win->mlx_connect, &to_draw, win);
	mlx_key_hook(win->mlx_win, arrow_keys, win);
	mlx_hook(win->mlx_win, KeyPress, KeyPressMask, check_event, win);
	mlx_hook(win->mlx_win, 17, 0, to_close, win);
	mlx_loop(win->mlx_connect);
}
