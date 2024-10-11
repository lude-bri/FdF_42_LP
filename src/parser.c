/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:09:09 by luigi             #+#    #+#             */
/*   Updated: 2024/10/09 20:18:33 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	count_words(char const *str, char c);

//this function get the dimensions of the map, calculating x and y
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
		error_clean(fd, "Error: Empty file\n");
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

//this function reads the map, getting the dimensions of x and y.
//then initialize the map with the coordenates. And reads the map,
//line by line. While the function reads the line, it fills the matrix
//of the map.
t_map	*read_map(char *filemap, int fd)
{
	t_map	*map;
	char	*line;
	t_z		*z;
	int		x;
	int		y;

	get_dimensions(&x, &y, filemap);
	map = malloc(sizeof(t_map));
	z = malloc(sizeof(t_z));
	init_map(map, x, y, z);
	y = 0;
	fd = open(filemap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		map->coord[y] = malloc(map->w * sizeof(t_point));
		fill_mtrx(map->coord[y], line, y, z);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	setup_colors(map, z);
	free(line);
	close(fd);
	return (map);
}

//this function takes a line and set the point x, y and z in the matrix.
//also verify the range of z to apply the customs colors
void	fill_mtrx(t_point *row, char *line, int y, t_z *z)
{
	char	**data;
	int		c;

	c = 0;
	data = ft_split(line, ' ');
	to_range_z(z, data);
	while (line[c])
	{
		if (line[c] == ' ' && line[c + 1] == '\n')
		{
			ft_printf("Error: Space followed by a new line\n");
			exit (0);
		}
		c++;
	}
	c = 0;
	while (data[c])
	{
		set_point(&row[c], data[c], c, y);
		free(data[c]);
		c++;
	}
	free(data);
}

//this function set the points of the map -> x, y and z.
//also verifies if there is colors (ex: 0,0xFFFFFF).
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
	{
		point->color = rgb_to_int(data[1]);
		point->check_color = true;
	}
	else
	{
		point->color = 0x00ff00;
		point->check_color = false;
	}
	free_args(data);
}

//this function count how many words there is in a string
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
