/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:09:09 by luigi             #+#    #+#             */
/*   Updated: 2024/10/03 14:05:38 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	count_words(char const *str, char c);

int	get_dimensions(int *x, int *y, char	*file)
{
	char	*line;
	int		fd;

	*y = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_clean(fd, "Error: Not a file or not enough permissions\n");
	line = get_next_line(fd);
	if (!line)
		error_clean(fd, "Error: No info on file\n");
	*x = count_words(line, ' ');
	while (line)
	{
		*y = *y + 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

t_map	*read_map(char *filemap)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		x;
	int		y;

	get_dimensions(&x, &y, filemap);
	map = malloc(sizeof(t_map));
	map->w = x;
	map->h = y;
	map->coord = malloc(map->h * sizeof(t_point *));
	y = 0;
	fd = open(filemap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		map->coord[y] = malloc(map->w * sizeof(t_point));
		fill_mtrx(map->coord[y], line, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (map);
}

void	fill_mtrx(t_point *row, char *line, int y)
{
	char	**data;
	int		c;

	c = 0;
	data = ft_split(line, ' ');
	while (data[c])
	{
		set_point(&row[c], data[c], c, y);
		free(data[c]);
		c++;
	}
	free(data);
}

void	set_point(t_point *point, char *str, int x, int y)
{
	char	**data;

	if (!*str || *str == '\n')
		return ;
	data = ft_split(str, ',');
	point->z = ft_atoi(data[0]);
	point->x = x;
	point->y = y;
	if (data[1])
		point->color = rgb_to_int(data[1]);
	else
	{
		range_z(point);
		point->color = 0xffff00;
	}
	free_args(data);
}

static int	count_words(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}
