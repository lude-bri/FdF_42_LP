/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:16:10 by luigi             #+#    #+#             */
/*   Updated: 2024/09/27 12:49:48 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

//this function deals with error
void	error_clean(int fd, char *str)
{
	ft_putstr_fd(str, 2);
	close(fd);
	exit(EXIT_FAILURE);
}

//this function free the arguments
void	free_args(char **numbers)
{
	int	i;

	i = 0;
	if (!numbers || !*numbers)
		return ;
	while (numbers[i] != NULL)
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

//this function free the map
void	free_map(t_map *map)
{
	int		c;

	c = -1;
	while (map->h > ++c)
		free(map->coord[c]);
	free(map->coord);
	free(map);
}

//this function erases the map and free everything
void	clean_and_exit(t_mlx *mlx)
{
	if (mlx->mlx_connect)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->img.mlx_img);
		if (mlx->mlx_win)
			mlx_destroy_window(mlx->mlx_connect, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
	}
	if (mlx->map)
		free_map(mlx->map);
	free(mlx);
	exit(0);
}

//this function closes and frees everything
int	to_close(t_mlx *mlx)
{
	clean_and_exit(mlx);
	return (0);
}
