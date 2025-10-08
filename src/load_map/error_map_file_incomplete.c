/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_file_incomplete.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:23:29 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:24:19 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include <stdbool.h>

bool	map_data_has_empty_fields(t_map_data *data)
{
	if (!data->north_wall_str)
		return (true);
	if (!data->east_wall_str)
		return (true);
	if (!data->south_wall_str)
		return (true);
	if (!data->west_wall_str)
		return (true);
	if (!data->floor_str)
		return (true);
	if (!data->ceiling_str)
		return (true);
	return (false);
}
