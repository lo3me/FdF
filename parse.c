/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:04:31 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/10 16:50:26 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_lines(int fd)
{
	char	*line;
	size_t	i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
		line = NULL;
	}
	return (i);
}

static void	write_row(t_point **points, char **v, size_t i, long int jz_max[2])
{
	long int	j;
	long int	z;
	t_point		p;

	points[i] = malloc((ft_split_len(v) + 1) * sizeof(t_point));
	if (!points[i])
		terminate("map (one of lines) too large", -1);
	j = 0;
	while (v[j])
	{
		z = ft_atoi(v[j]);
		if (z > jz_max[1])
			jz_max[1] = z;
		p = (t_point){.x = j, .y = i, .x0 = j, .y0 = i, .z = z, .z0 = z,
			.eol = 0};
		points[i][j] = p;
		j++;
	}
	points[i][j] = (t_point){.x = 0, .y = 0, .z = 0, .z0 = 0, .eol = 1};
	if (j > jz_max[0])
		jz_max[0] = j;
}

static void	file_into_map(int fd, t_map *map)
{
	char		*line;
	char		**vertices;
	size_t		i;
	long int	jz_max[2];

	ft_bzero(jz_max, sizeof(jz_max));
	lseek(fd, 0, SEEK_SET);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		vertices = ft_split(line, ' ');
		free(line);
		write_row(map->points, vertices, i++, jz_max);
		ft_free_split(vertices);
		vertices = NULL;
	}
	map->points[i] = NULL;
	map->height = i;
	map->width = jz_max[0];
	map->depth = jz_max[1];
}

t_map	*map_from_file(int fd)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->points = malloc((count_lines(fd) + 1) * sizeof(t_point *));
	if (!map->points)
		terminate("map (rows) too large", -1);
	file_into_map(fd, map);
	return (map);
}
