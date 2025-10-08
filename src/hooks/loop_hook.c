/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:57:52 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 19:28:03 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/draw.h"
#include "../../inc/player_movement.h"
#include "../../inc/minimap.h"
#include "../../inc/render.h"
#include "../../inc/input.h"
#include "../../inc/raycasting.h"
#include <stdio.h>

static void	update_screen(t_game *game);

void	loop_hook(void *param)
{
	t_game			*game;

	game = (t_game *) param;
	get_input(game);
	player_move(game);
	cast_rays(game);
	update_screen(game);
	update_minimap(game);
	printf("%f\n", 1 / game->mlx->delta_time);
}

static void	update_screen(t_game *game)
{
	t_rect	ceiling;
	t_rect	floor;

	ceiling = new_rect(0, 0, WIDTH, HEIGHT);
	floor = new_rect(0, HEIGHT / 2 + HEIGHT % 2, WIDTH, HEIGHT / 2);
	if (!game->map->ceiling.is_texture)
		draw_rect(game->screen, &ceiling, game->map->ceiling.u_asset.color);
	if (!game->map->floor.is_texture)
		draw_rect(game->screen, &floor, game->map->floor.u_asset.color);
	if (game->map->ceiling.is_texture || game->map->floor.is_texture)
		render_floor_and_ceiling_textures(game);
	render_walls(game);
}
