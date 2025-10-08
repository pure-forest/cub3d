/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:14:44 by juaho             #+#    #+#             */
/*   Updated: 2025/08/06 20:14:42 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/player_movement.h"
#include "../../inc/game.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	static bool		is_initialized = false;
	static double	prev_x = 0;

	(void)ypos;
	game = (t_game *) param;
	if (is_initialized)
		player_rotate(game, (xpos - prev_x) * TURN_RATE_MOUSE);
	else
		is_initialized = true;
	prev_x = xpos;
}
