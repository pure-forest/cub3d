/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:29:19 by ydeng             #+#    #+#             */
/*   Updated: 2025/08/04 17:37:32 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/render.h"
#include "../../inc/map.h"
#include "../../libft/libft.h"
#include <math.h>

static void	get_tex_column(t_ray ray_data, t_render *render_data, int width);
static void	render_column(t_game *game, t_texture *texture, uint32_t column);
static void	textured_column(t_game *game, mlx_texture_t *tx, uint32_t column);
static void	solid_column(t_game *game, uint32_t color, uint32_t column);

void	render_walls(t_game *game)
{
	uint32_t	column;

	column = 0;
	while (column < WIDTH)
	{
		if (game->ray_data[column].collision_face == NORTH)
			render_column(game, &game->map->north_wall, column);
		else if (game->ray_data[column].collision_face == SOUTH)
			render_column(game, &game->map->south_wall, column);
		else if (game->ray_data[column].collision_face == EAST)
			render_column(game, &game->map->east_wall, column);
		else
			render_column(game, &game->map->west_wall, column);
		column++;
	}
}

static void	render_column(t_game *game, t_texture *texture, uint32_t column)
{
	if (texture->is_texture)
		textured_column(game, texture->u_asset.texture, column);
	else
		solid_column(game, texture->u_asset.color, column);
}

static void	textured_column(t_game *game, mlx_texture_t *tx, uint32_t column)
{
	uint32_t	y;
	uint32_t	y0;
	uint32_t	y1;
	t_render	r;
	int			tx_index;

	r.column_h = HEIGHT / game->ray_data[column].dist;
	r.screen_pixel = (uint32_t *) game->screen->pixels;
	r.texture_pixel = (uint32_t *) tx->pixels;
	y0 = HEIGHT / 2 - r.column_h / 2;
	y1 = ft_min(HEIGHT / 2 + r.column_h / 2, HEIGHT);
	y = ft_max(0, y0);
	while (y < y1)
	{
		r.texture_row = (y - y0) * tx->height / r.column_h;
		get_tex_column(game->ray_data[column], &r, tx->width);
		tx_index = r.texture_column + r.texture_row * tx->width;
		r.screen_pixel[column + y * WIDTH] = r.texture_pixel[tx_index];
		y++;
	}
}

static void	get_tex_column(t_ray ray_data, t_render *render_data, int width)
{
	if (ray_data.collision_face == NORTH)
		render_data->texture_column = width * (1 - fmod(ray_data.end.x, 1));
	else if (ray_data.collision_face == SOUTH)
		render_data->texture_column = width * fmod(ray_data.end.x, 1);
	else if (ray_data.collision_face == EAST)
		render_data->texture_column = width * (1 - fmod(ray_data.end.y, 1));
	else
		render_data->texture_column = width * fmod(ray_data.end.y, 1);
}

static void	solid_column(t_game *game, uint32_t color, uint32_t column)
{
	uint32_t		y;
	uint32_t		y0;
	uint32_t		y1;
	t_render		r;

	r.column_h = HEIGHT / game->ray_data[column].dist;
	r.screen_pixel = (uint32_t *) game->screen->pixels;
	y0 = HEIGHT / 2 - r.column_h / 2;
	y1 = ft_min(HEIGHT / 2 + r.column_h / 2, HEIGHT);
	y = ft_max(0, y0);
	while (y < y1)
	{
		r.screen_pixel[column + y * WIDTH] = color;
		y++;
	}
}
