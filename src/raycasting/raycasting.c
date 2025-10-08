/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:19:45 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 14:58:21 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/raycasting.h"
#include "../../inc/defs.h"
#include <math.h>

void	cast_rays(t_game *game)
{
	const double	fov_rad = FOV / 180.0 * M_PI;
	const double	camera_plane_len = tan(fov_rad / 2);
	t_vec2			camera_plane;
	t_vec2			ray_dir;
	uint32_t		col;

	camera_plane.x = -game->player.dir.y * camera_plane_len;
	camera_plane.y = game->player.dir.x * camera_plane_len;
	vec2_assign(&ray_dir, &game->player.dir);
	vec2_diff(&ray_dir, &camera_plane);
	col = 0;
	while (col < WIDTH)
	{
		ray_dir.x += camera_plane.x * 2 / WIDTH;
		ray_dir.y += camera_plane.y * 2 / WIDTH;
		game->ray_data[col] = cast_ray(game->map, &game->player, &ray_dir);
		col++;
	}
}
