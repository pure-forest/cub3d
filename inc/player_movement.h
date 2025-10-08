/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:31:43 by ydeng             #+#    #+#             */
/*   Updated: 2025/07/24 00:27:56 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_MOVEMENT_H
# define PLAYER_MOVEMENT_H
# include "../inc/game.h"

////////////////////////////////////////// player_movement/player_movement.c //

/**
 * Moves according to it's velocity in relation to where the player direction.
 *
 * @param	game
 * 		Pointer to the game struct.
 */
void	player_move(t_game *game);

/**
 * Rotates the player by the given step. A positive step will result in counter-
 * clockwise rotation and vice versa.
 *
 * @param	game
 * 		Pointer to the game struct.
 *
 * @param	step
 * 		The amount of radians to rotate.
 */
void	player_rotate(t_game *game, double step);

/**
 * Checks if the player is inside a wall.
 *
 * @param	game
 * 		Pointer to game struct.
 *
 * @return
 * 		True on collision, false on none.
 */
bool	collision_check(t_game *game);

#endif
