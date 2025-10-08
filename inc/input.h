/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:11:00 by juaho             #+#    #+#             */
/*   Updated: 2025/08/02 13:36:39 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "../inc/game.h"

/**
 * Reads and reacts to keyboard and mouse input, updating the game state, mostly
 * the player's position and direction and such.
 *
 * @param	game
 * 		The game struct.
 */
void	get_input(t_game *game);

#endif
