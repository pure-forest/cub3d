/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:23:22 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:33:04 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/map.h"
#include "../../inc/errors.h"
#include <stdbool.h>

static int32_t	validate_grid(t_map *map);
static bool		is_touching_void(t_map *map, uint32_t x, uint32_t y);
static bool		map_has_only_one_player_spawn(t_map *map);

bool	is_valid_map(t_map *map)
{
	int32_t	ret;

	if (!map_has_only_one_player_spawn(map))
	{
		print_error("Map contains more or less than one player spawn", NULL);
		return (false);
	}
	ret = validate_grid(map);
	if (ret == 1)
		print_error("Map grid contains invalid characters.", NULL);
	if (ret == 2)
		print_error("Map has floors unseparated from the void.", NULL);
	return (ret == 0);
}

static bool	map_has_only_one_player_spawn(t_map *map)
{
	bool		spawn_found;
	uint32_t	x;
	uint32_t	y;

	spawn_found = false;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (ft_strchr("NSWE", map->grid[x + y * map->w]))
			{
				if (spawn_found)
					return (false);
				spawn_found = true;
			}
			x++;
		}
		y++;
	}
	return (spawn_found);
}

static int32_t	validate_grid(t_map *map)
{
	uint32_t	x;
	uint32_t	y;
	char		c;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			c = map->grid[x + y * map->w];
			if (!ft_strchr(" 01NSWE", c))
				return (1);
			if (ft_strchr("0NSWE", c))
				if (is_touching_void(map, x, y))
					return (2);
			x++;
		}
		y++;
	}
	return (0);
}

static bool	is_touching_void(t_map *map, uint32_t x, uint32_t y)
{
	uint32_t	off_x;
	uint32_t	off_y;

	if (x == 0 || x + 1 == map->w || y == 0 || y + 1 == map->h)
		return (true);
	off_x = x - 1;
	off_y = y - 1;
	while (1)
	{
		if (map->grid[off_x + off_y * map->w] == ' ')
			return (true);
		off_x++;
		if (off_y == y && off_x == x)
			off_x++;
		if (off_x > x + 1)
		{
			off_x = x - 1;
			off_y++;
			if (off_y > y + 1)
				break ;
		}
	}
	return (false);
}
