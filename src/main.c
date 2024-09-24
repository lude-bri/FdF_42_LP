/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:11:51 by luigi             #+#    #+#             */
/*   Updated: 2024/09/23 23:45:23 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mlx/mlx.h"
#include <stdlib.h>

#define W 800
#define H 500

int	main(void)
{
	void	*mlx;
	void	*mlx_window;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, W, H, "FdF");
	for (int y = H * 0.1; y < H * 0.9; y++)
	{
		for (int x = W * 0.1; x < W * 0.9; x++)
		{
			mlx_pixel_put(mlx, mlx_window, x, y, rand() % 0x100000);
		}
	}
	mlx_loop(mlx);
}
