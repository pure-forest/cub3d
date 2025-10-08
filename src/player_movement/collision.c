/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:48:23 by juaho             #+#    #+#             */
/*   Updated: 2025/08/02 13:03:16 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/defs.h"

bool	collision_check(t_game *game)
{
	const double	player_half = (double) PLAYER_SIZE / TILE_SIZE / 2;
	t_gobj			*player;
	t_vec2i			posi;

	player = &game->player;
	posi.x = (int32_t)(player->pos.x + player_half);
	posi.y = (int32_t)(player->pos.y + player_half);
	if (game->map->grid[posi.x + posi.y * game->map->w] == '1')
		return (true);
	posi.x = (int32_t)(player->pos.x - player_half);
	posi.y = (int32_t)(player->pos.y + player_half);
	if (game->map->grid[posi.x + posi.y * game->map->w] == '1')
		return (true);
	posi.x = (int32_t)(player->pos.x + player_half);
	posi.y = (int32_t)(player->pos.y - player_half);
	if (game->map->grid[posi.x + posi.y * game->map->w] == '1')
		return (true);
	posi.x = (int32_t)(player->pos.x - player_half);
	posi.y = (int32_t)(player->pos.y - player_half);
	if (game->map->grid[posi.x + posi.y * game->map->w] == '1')
		return (true);
	return (false);
}
