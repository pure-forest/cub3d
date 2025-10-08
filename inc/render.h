/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:59:46 by ydeng             #+#    #+#             */
/*   Updated: 2025/08/04 17:31:06 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "raycasting.h"

typedef struct s_game	t_game;

/**
 * Struct that holds the data needed for rendering
 *
 * @param	texture_pixel
 * 		a pixel pointer that is used to intialize for the imported texture
 * @param	screen_pixel
 * 		a pixel pointer that is used to render the screen image pixel by pixel
 * @param	texture_row
 * 		an integer that is used to storage which row of the pixel will be
 * 		used to render the walls
 * @param	texture_column
 * 		an integer that is used to storage which column of the pixel will be
 * 		used to render the walls
 */
typedef struct s_render
{
	uint32_t		*texture_pixel;
	uint32_t		*screen_pixel;
	uint32_t		column_h;
	uint32_t		texture_row;
	uint32_t		texture_column;
}		t_render;

//////////////////////////////////////////////////////////// render/render.c //

/**
 * A function that draws the wall based on casted ray, it draw the walls column
 * by column by using a loop that will iterate the same amount as the screen
 * width.
 *
 * @param	game
 * 		The struct that contains the t_ray data, which is necessary for
 * 		rendering the columns;
 */
void	render_walls(t_game *game);

////////////////////////////////////////// render/render_floor_and_ceiling.c //

/**
 * Renders the floor and ceiling textures.
 *
 * @param	game
 * 		The game struct.
 */
void	render_floor_and_ceiling_textures(t_game *game);

#endif
