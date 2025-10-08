/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:07:09 by juaho             #+#    #+#             */
/*   Updated: 2025/08/06 20:14:17 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/player_movement.h"
#include "../../inc/hooks.h"

static void	get_wasd(t_game *game);

void	get_input(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_hook(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player_rotate(game, -TURN_RATE_KB);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player_rotate(game, TURN_RATE_KB);
	get_wasd(game);
}

static void	get_wasd(t_game *game)
{
	t_gobj	*player;

	player = &game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		player->vel.x += player->dir.x;
		player->vel.y += player->dir.y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		player->vel.x -= player->dir.x;
		player->vel.y -= player->dir.y;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		player->vel.x += player->dir.y;
		player->vel.y -= player->dir.x;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		player->vel.x -= player->dir.y;
		player->vel.y += player->dir.x;
	}
}
