/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:31:07 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 17:37:26 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../libft/libft.h"
#include <stdlib.h>

void	free_map(t_map *map)
{
	if (map->north_wall.is_texture)
		mlx_delete_texture(map->north_wall.u_asset.texture);
	if (map->east_wall.is_texture)
		mlx_delete_texture(map->east_wall.u_asset.texture);
	if (map->south_wall.is_texture)
		mlx_delete_texture(map->south_wall.u_asset.texture);
	if (map->west_wall.is_texture)
		mlx_delete_texture(map->west_wall.u_asset.texture);
	if (map->floor.is_texture)
		mlx_delete_texture(map->floor.u_asset.texture);
	if (map->ceiling.is_texture)
		mlx_delete_texture(map->ceiling.u_asset.texture);
	free(map->grid);
	ft_bzero(map, sizeof(t_map));
}

void	free_map_data(t_map_data *data)
{
	free(data->east_wall_str);
	free(data->west_wall_str);
	free(data->north_wall_str);
	free(data->south_wall_str);
	free(data->ceiling_str);
	free(data->floor_str);
	ft_bzero(data, sizeof(t_map_data));
}

bool	check_suffix(const char *string, const char *suffix)
{
	const uint32_t	string_len = ft_strlen(string);
	const uint32_t	suffix_len = ft_strlen(suffix);
	uint32_t		index;

	if (suffix_len > string_len)
		return (false);
	string += string_len - suffix_len;
	index = 0;
	while (string[index])
	{
		if (string[index] != suffix[index])
			return (false);
		index++;
	}
	return (string[index] == suffix[index]);
}
