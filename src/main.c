/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:11:51 by luigi             #+#    #+#             */
/*   Updated: 2024/09/26 12:52:21 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdlib.h>

#define W 500
#define H 500

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
			render(map); //to_write
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




// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_window;
//
// 	mlx = mlx_init();
// 	mlx_window = mlx_new_window(mlx, W, H, "FdF");
// 	for (int y = H * 0.1; y < H * 0.9; y++)
// 	{
// 		for (int x = W * 0.1; x < W * 0.9; x++)
// 		{
// 			mlx_pixel_put(mlx, mlx_window, x, y, rand() % 0x100000);
// 		}
// 	}
// 	mlx_loop(mlx);
// }
//
//
// typedef struct	s_vars
// {
// 	void	*mlx;
// 	void	*win;
// }			t_vars;
//
// static int	close(t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	mlx_destroy_display(vars->mlx);
// 	exit (0);
// }
//
// int	main(void)
// {
// 	t_vars	vars;
//
// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, W, H, "Test");
// 	for (int y = H * 0.1; y < H * 0.9; y++)
// 	{
// 		for (int x = W * 0.1; x < W * 0.9; x++)
// 		{
// 			mlx_pixel_put(vars.mlx, vars.win, x, y, 0x00ff00);
// 		}
// 	}
// 	for (int y = H * 0.2; y < H * 0.8; y++)
// 	{
// 		for (int x = W * 0.2; x < W * 0.8; x++)
// 		{
// 			mlx_pixel_put(vars.mlx, vars.win, x, y, 0xff0000);
// 		}
// 	}
// 	mlx_hook(vars.win, 17, 2, close, &vars);
// 	mlx_loop(vars.mlx);
// }
