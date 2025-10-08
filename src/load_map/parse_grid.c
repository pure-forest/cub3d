/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:28:17 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:28:56 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/errors.h"
#include "../../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

static char	*get_map_grid_from_fd(char **line, int32_t fd);
static bool	append(char **dst, char *append);
static void	get_map_grid_dimensions(t_map *map, char *map_grid);
static bool	pad_map_with_spaces(t_map *map, char *map_grid);

bool	parse_grid(char **line, t_map *map, int32_t fd)
{
	char	*map_grid;
	bool	ret;

	map_grid = get_map_grid_from_fd(line, fd);
	if (!map_grid)
		return (false);
	get_map_grid_dimensions(map, map_grid);
	ret = true;
	if (!pad_map_with_spaces(map, map_grid))
		ret = false;
	free(map_grid);
	return (ret);
}

static char	*get_map_grid_from_fd(char **line, int32_t fd)
{
	char	*joined_line;

	joined_line = NULL;
	while (1)
	{
		if (!append(&joined_line, *line))
		{
			print_error("ft_strjoin", strerror(errno));
			break ;
		}
		free(*line);
		*line = get_next_line(fd);
		if (!*line)
		{
			if (!errno)
				return (joined_line);
			print_error("get_next_line", strerror(errno));
			break ;
		}
	}
	free(*line);
	free(joined_line);
	return (NULL);
}

static bool	append(char **dst, char *append)
{
	char		*appended;

	if (!*dst)
	{
		if (*append != '\n')
		{
			*dst = ft_strdup(append);
			if (!*dst)
				return (false);
		}
		return (true);
	}
	appended = ft_strjoin(*dst, append);
	if (!appended)
		return (false);
	free(*dst);
	*dst = appended;
	return (true);
}

static void	get_map_grid_dimensions(t_map *map, char *map_grid)
{
	uint32_t	w;

	map->w = 0;
	map->h = 0;
	while (*map_grid == '\n')
		map_grid++;
	while (*map_grid)
	{
		w = 0;
		while (map_grid[w] && map_grid[w] != '\n')
			w++;
		if (w > map->w)
			map->w = w;
		map->h++;
		map_grid += w + 1;
	}
}

static bool	pad_map_with_spaces(t_map *map, char *map_grid)
{
	uint32_t	x;
	uint32_t	y;

	map->grid = (char *) malloc(sizeof(char) * map->w * map->h);
	if (!map->grid)
		return (false);
	y = 0;
	while (*map_grid)
	{
		x = 0;
		while (*map_grid && *map_grid != '\n')
		{
			map->grid[x + y * map->w] = *map_grid;
			x++;
			map_grid++;
		}
		while (x < map->w)
		{
			map->grid[x + y * map->w] = ' ';
			x++;
		}
		y++;
		map_grid++;
	}
	return (true);
}
