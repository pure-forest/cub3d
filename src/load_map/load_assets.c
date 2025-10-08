/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:39:30 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:45:59 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/errors.h"
#include "../../inc/color.h"
#include "../../libft/libft.h"

static void	texture_or_color(t_map *map, t_map_data *data);
static bool	is_color(char *string);
static bool	load_asset(char *string, t_texture *texture);

bool	load_assets(t_map *map, t_map_data *data)
{
	texture_or_color(map, data);
	if (!load_asset(data->north_wall_str, &map->north_wall))
		return (false);
	if (!load_asset(data->east_wall_str, &map->east_wall))
		return (false);
	if (!load_asset(data->south_wall_str, &map->south_wall))
		return (false);
	if (!load_asset(data->west_wall_str, &map->west_wall))
		return (false);
	if (!load_asset(data->floor_str, &map->floor))
		return (false);
	if (!load_asset(data->ceiling_str, &map->ceiling))
		return (false);
	return (true);
}

static void	texture_or_color(t_map *map, t_map_data *data)
{
	map->north_wall.is_texture = !is_color(data->north_wall_str);
	map->east_wall.is_texture = !is_color(data->east_wall_str);
	map->south_wall.is_texture = !is_color(data->south_wall_str);
	map->west_wall.is_texture = !is_color(data->west_wall_str);
	map->ceiling.is_texture = !is_color(data->ceiling_str);
	map->floor.is_texture = !is_color(data->floor_str);
}

static bool	is_color(char *string)
{
	uint8_t	color_channels;
	uint8_t	digits;

	color_channels = 0;
	while (true)
	{
		if (!ft_isdigit(*string))
			return (false);
		digits = 0;
		while (ft_isdigit(*string))
		{
			digits++;
			if (digits > 3)
				return (false);
			string++;
		}
		color_channels++;
		if (color_channels == 3)
			break ;
		if (*(string++) != ',')
			return (false);
		while (*string == ' ')
			string++;
	}
	return (*string == '\0');
}

static bool	load_asset(char *string, t_texture *texture)
{
	if (texture->is_texture)
	{
		if (!check_suffix(string, ".png"))
		{
			print_error("Invalid texture path or color", string);
			return (false);
		}
		texture->u_asset.texture = mlx_load_png(string);
		if (!texture->u_asset.texture)
		{
			print_error(mlx_strerror(mlx_errno), string);
			return (false);
		}
		return (true);
	}
	if (!string_to_color(string, &texture->u_asset.color))
	{
		print_error("Invalid color", string);
		return (false);
	}
	return (true);
}
