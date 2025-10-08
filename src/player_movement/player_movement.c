/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:31:35 by juaho             #+#    #+#             */
/*   Updated: 2025/07/24 00:22:30 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/player_movement.h"
#include "../../inc/defs.h"
#include <math.h>

static void	diagonal_movement_speed_correction(t_gobj *player);

void	player_move(t_game *game)
{
	const double	step = game->mlx->delta_time * MOVE_SPEED;
	t_gobj			*player;

	player = &game->player;
	diagonal_movement_speed_correction(player);
	player->pos.x += player->vel.x * step;
	if (collision_check(game))
		player->pos.x -= player->vel.x * step;
	player->pos.y += player->vel.y * step;
	if (collision_check(game))
		player->pos.y -= player->vel.y * step;
	player->vel.x = 0;
	player->vel.y = 0;
}

static void	diagonal_movement_speed_correction(t_gobj *player)
{
	const double	speed = sqrt(pow(player->vel.x, 2) + pow(player->vel.y, 2));
	double			angle;

	if (speed <= 1)
		return ;
	angle = atan2(player->vel.y, player->vel.x);
	player->vel.x = cos(angle);
	player->vel.y = sin(angle);
}

void	player_rotate(t_game *game, double step)
{
	t_gobj			*player;

	step *= game->mlx->delta_time;
	player = &game->player;
	player->angle += step;
	while (player->angle >= M_PI * 2)
		player->angle -= M_PI * 2;
	while (player->angle < 0)
		player->angle += M_PI * 2;
	player->dir.x = cos(player->angle);
	player->dir.y = sin(player->angle);
}
