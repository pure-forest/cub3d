/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:10:39 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 11:59:18 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycasting.h"
#include "../../inc/map.h"
#include "../../inc/game.h"
#include "../../inc/defs.h"
#include "../../inc/vec2.h"
#include "../../inc/errors.h"
#include <math.h>

static bool	its_a_hit(const t_map *map, t_vec2 *ray_end, const t_vec2 *dir);
static bool	out_of_bounds(const t_map *map, t_vec2 *ray_end);
static void	get_step(t_vec2 *step, t_vec2 *pos, const t_vec2 *dir);
static void	set_ray_data(t_ray *ray, const t_gobj *origin, const t_vec2 *dir);

t_ray	cast_ray(t_map *map, const t_gobj *origin, const t_vec2 *dir)
{
	t_ray	ray;
	t_vec2	delta_len;
	t_vec2	step;

	delta_len.x = sqrt(1 + pow(dir->y / dir->x, 2));
	delta_len.y = sqrt(1 + pow(dir->x / dir->y, 2));
	vec2_assign(&ray.end, &origin->pos);
	while (1)
	{
		if (its_a_hit(map, &ray.end, dir))
			break ;
		get_step(&step, &ray.end, dir);
		if (fabs(step.x * delta_len.x) < fabs(step.y * delta_len.y))
		{
			ray.end.x += step.x;
			ray.end.y += step.x * (dir->y / dir->x);
		}
		else
		{
			ray.end.y += step.y;
			ray.end.x += step.y * (dir->x / dir->y);
		}
	}
	set_ray_data(&ray, origin, dir);
	return (ray);
}

static bool	its_a_hit(const t_map *map, t_vec2 *ray_end, const t_vec2 *dir)
{
	t_vec2i	map_coord;

	if (out_of_bounds(map, ray_end))
	{
		print_error("Ray in the void.", NULL);
		return (true);
	}
	vec2i_trunc(&map_coord, ray_end);
	if (fmod(ray_end->x, 1) == 0)
		if (dir->x < 0)
			map_coord.x--;
	if (fmod(ray_end->y, 1) == 0)
		if (dir->y < 0)
			map_coord.y--;
	return (map->grid[map_coord.x + map_coord.y * map->w] == '1');
}

static bool	out_of_bounds(const t_map *map, t_vec2 *ray_end)
{
	if (ray_end->x < 0)
	{
		ray_end->x = 0;
		return (true);
	}
	if (ray_end->x >= map->w * TILE_SIZE)
	{
		ray_end->x = map->w * TILE_SIZE - 1;
		return (true);
	}
	if (ray_end->y < 0)
	{
		ray_end->y = 0;
		return (true);
	}
	if (ray_end->y >= map->h * TILE_SIZE)
	{
		ray_end->y = map->h * TILE_SIZE - 1;
		return (true);
	}
	return (false);
}

static void	get_step(t_vec2 *step, t_vec2 *pos, const t_vec2 *dir)
{
	step->x = -fmod(pos->x, 1);
	if (dir->x > 0)
		step->x += 1;
	else
		if (step->x == 0)
			step->x = -1;
	step->y = -fmod(pos->y, 1);
	if (dir->y > 0)
		step->y += 1;
	else
		if (step->y == 0)
			step->y = -1;
}

static void	set_ray_data(t_ray *ray, const t_gobj *origin, const t_vec2 *dir)
{
	const double	angle_delta = atan2(dir->y, dir->x) - origin->angle;
	t_vec2			delta;

	delta.x = fabs(origin->pos.x - ray->end.x);
	delta.y = fabs(origin->pos.y - ray->end.y);
	ray->dist = cos(angle_delta) * sqrt(delta.x * delta.x + delta.y * delta.y);
	if (fmod(ray->end.x, 1) == 0)
	{
		if (dir->x < 0)
			ray->collision_face = EAST;
		else
			ray->collision_face = WEST;
	}
	else
	{
		if (dir->y < 0)
			ray->collision_face = SOUTH;
		else
			ray->collision_face = NORTH;
	}
	vec2_assign(&ray->dir, dir);
}
