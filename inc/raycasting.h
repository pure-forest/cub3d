/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:11:54 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 11:58:13 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "../inc/vec2.h"

// Forward declarations.
typedef struct s_game	t_game;
typedef struct s_map	t_map;
typedef struct s_gobj	t_gobj;

/**
 * Represents a single ray cast with cast_ray().
 *
 * @param	end
 * 		The coordinates of the end point of the ray.
 *
 * @param	dir
 * 		The direction of the ray.
 *
 * @param	dist
 * 		The "perpendicular distance" calculated from a camera plane. This is
 * 		required to render walls without fish-eye distortion.
 *
 * @param	collision_face
 * 		Which face of a wall block the ray hit. (NORTH, EAST, SOUTH, WEST)
 *
 */
typedef struct s_ray
{
	t_vec2	end;
	t_vec2	dir;
	double	dist;
	uint8_t	collision_face;
}	t_ray;

////////////////////////////////////////////////////// raycasting/cast_ray.c //

/**
 * Casts a ray from given position with the given direction. The map is used to
 * calculate when the ray hits a wall. Returns a t_ray struct with the
 * perpendicular distance of the end from the camera plane used for rendering,
 * the face of the wall it collided with, and the coordinates of the end point,
 * where the ray collided with a wall or map boundary.
 *
 * @param	map
 * 		Map struct used for wall detection.
 *
 * @param	origin
 * 		The game object where the ray is cast from.
 *
 * @param	dir
 * 		The ray's direction.
 *
 * @return
 * 		The resulting ray is returned.
 */
t_ray	cast_ray(t_map *map, const t_gobj *origin, const t_vec2 *dir);

//////////////////////////////////////////////////// raycasting/raycasting.c //

/**
 * Casts a ray for every pixel of width on the game window.
 *
 * @param	game
 * 		The game struct.
 */
void	cast_rays(t_game *game);

#endif
