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
static void to_range_z(t_z *z, char **data);
static int	find_min(char **data);
static int	find_max(char **data);

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
	t_z		*z;
	int		fd;
	int		x;
	int		y;

	get_dimensions(&x, &y, filemap);
	map = malloc(sizeof(t_map));
	z = malloc(sizeof(t_z));
	map->w = x;
	map->h = y;
	z->z_max = 0;
	z->z_min = 0;
	map->coord = malloc(map->h * sizeof(t_point *));
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
	if (check_color_true(map) == false)
		apply_color_grading(map, z);
	free(line);
	close(fd);
	return (map);
}

void	fill_mtrx(t_point *row, char *line, int y, t_z *z)
{
	char	**data;
	int		c;

	c = 0;
	data = ft_split(line, ' ');
	to_range_z(z, data);
	while (data[c])
	{
		set_point(&row[c], data[c], c, y);
		free(data[c]);
		c++;
	}
	free(data);
}

static void to_range_z(t_z *z, char **data)
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

static int	find_max(char **data)
{
	int		i;
	int		max;
	int		current_value;

	if (!data || !*data[0])
		return (0);
	i = 0;
	max = ft_atoi(data[0]);  // Initialize max with the first value
	while (data[i])
	{
		current_value = ft_atoi(data[i]);  // Convert current string to integer
		if (current_value > max)  // Check if current value is greater than max
			max = current_value;  // Update max if needed
		i++;
	}
	return (max);  // Return the maximum value found
}

static int	find_min(char **data)
{
	int		i;
	int		min;
	int		current_value;

	i = 0;
	min = ft_atoi(data[0]);  // Initialize min with the first value
	while (data[i])
	{
		current_value = ft_atoi(data[i]);  // Convert current string to integer
		if (current_value < min)  // Check if current value is less than min
			min = current_value;  // Update min if needed
		i++;
	}
	return (min);  // Return the minimum value found
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
	{
		point->color = rgb_to_int(data[1]);
		point->check_color = true;
	}
	else
		point->color = 0x00ff00;
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
