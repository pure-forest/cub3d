/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:51:51 by juaho             #+#    #+#             */
/*   Updated: 2025/08/06 20:16:55 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

////////////////////////////////////////////////////////// hooks/loop_hook.c //

/**
 * The main game loop. Gets input and updates the screen.
 *
 * @param	param
 * 		Expects a t_game struct pointer.
 */
void	loop_hook(void *param);

///////////////////////////////////////////////////////// hooks/close_hook.c //

/**
 * Callback to close the game cleanly on MLX42 close hook events.
 *
 * @param	param
 * 		Expects a t_game struct pointer.
 */
void	close_hook(void *param);

//////////////////////////////////////////////////////// hooks/cursor_hook.c //

/**
 * Callback to respond to mouse movement.
 *
 * @param	xpos
 * 		X position of the mouse, provided by MLX42.
 *
 * @param	ypos
 * 		Y position of the mouse, provided by MLX42.
 *
 * @param	param
 * 		Expects a t_game struct pointer.
 */
void	cursor_hook(double xpos, double ypos, void *param);

#endif
