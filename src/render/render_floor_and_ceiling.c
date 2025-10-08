/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:50:55 by juaho             #+#    #+#             */
/*   Updated: 2025/08/06 20:34:55 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/defs.h"
#include <math.h>

static void	get_floor_step(t_game *game, t_vec2 *floor_step, double row_dist);
static void	draw_row_pixel(t_game *game, t_vec2i *screen, t_vec2 floor);
static void	draw_floor_pixel(t_game *game, t_vec2i *screen, t_vec2 tile);
static void	draw_ceiling_pixel(t_game *game, t_vec2i *screen, t_vec2 tile);

void	render_floor_and_ceiling_textures(t_game *game)
{
	t_vec2i		screen;
	t_vec2		floor_step;
	t_vec2		floor;
	double		row_dist;

	screen.y = HEIGHT / 2 + 1;
	while (screen.y < HEIGHT)
	{
		row_dist = (HEIGHT * 0.5) / (int32_t)(screen.y - HEIGHT / 2);
		get_floor_step(game, &floor_step, row_dist);
		floor.x = game->player.pos.x + row_dist * game->ray_data[0].dir.x;
		floor.y = game->player.pos.y + row_dist * game->ray_data[0].dir.y;
		screen.x = 0;
		while (screen.x < WIDTH)
		{
			draw_row_pixel(game, &screen, floor);
			floor.x += floor_step.x;
			floor.y += floor_step.y;
			screen.x++;
		}
		screen.y++;
	}
}

static void	get_floor_step(t_game *game, t_vec2 *floor_step, double row_dist)
{
	const t_vec2	ray_dir0 = game->ray_data[0].dir;
	const t_vec2	ray_dir1 = game->ray_data[WIDTH - 1].dir;

	floor_step->x = row_dist * (ray_dir1.x - ray_dir0.x) / WIDTH;
	floor_step->y = row_dist * (ray_dir1.y - ray_dir0.y) / WIDTH;
}

static void	draw_row_pixel(t_game *game, t_vec2i *screen, t_vec2 floor)
{
	t_vec2				tile;

	tile.x = fmod(floor.x, 1);
	if (tile.x < 0)
		tile.x += 1;
	tile.y = fmod(floor.y, 1);
	if (tile.y < 0)
		tile.y += 1;
	if (game->map->floor.is_texture)
		draw_floor_pixel(game, screen, tile);
	if (game->map->ceiling.is_texture)
		draw_ceiling_pixel(game, screen, tile);
}

static void	draw_floor_pixel(t_game *game, t_vec2i *screen, t_vec2 tile)
{
	const mlx_texture_t	*texture = game->map->floor.u_asset.texture;
	const uint32_t		*texture_pixels = (uint32_t *) texture->pixels;
	t_vec2i				texel;
	uint32_t			pixel;

	texel.x = tile.x * texture->width;
	texel.y = tile.y * texture->height;
	pixel = texture_pixels[texel.x + texel.y * texture->width];
	((uint32_t *)game->screen->pixels)[screen->x + screen->y * WIDTH] = pixel;
}

static void	draw_ceiling_pixel(t_game *game, t_vec2i *screen, t_vec2 tile)
{
	const mlx_texture_t	*texture = game->map->ceiling.u_asset.texture;
	const uint32_t		*texture_pixels = (uint32_t *) texture->pixels;
	t_vec2i				texel;
	uint32_t			pixel;

	texel.x = tile.x * texture->width;
	texel.y = tile.y * texture->height;
	pixel = texture_pixels[texel.x + texel.y * texture->width];
	((uint32_t *)game->screen->pixels)[screen->x + (HEIGHT - screen->y - 1)
		* WIDTH] = pixel;
}
