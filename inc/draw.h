/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:14:44 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 14:50:08 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../inc/vec2.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_rect
{
	int32_t		x;
	int32_t		y;
	uint32_t	w;
	uint32_t	h;
}	t_rect;

//////////////////////////////////////////////////////////////// draw/draw.c //

/**
 * Fills the whole image with given color.
 *
 * @param	img
 * 		The image.
 *
 * @param	color
 * 		The color.
 */
void	fill_image(mlx_image_t *img, uint32_t color);

/**
 * Draws a rectangle of solid color onto an image.
 *
 * @param	img
 * 		Image to be drawn onto.
 *
 * @param	rect
 * 		The rectangle struct that will be drawn.
 *
 * @param	color
 * 		Color of the rectangle
 */
void	draw_rect(mlx_image_t *img, t_rect *rect, uint32_t color);

/////////////////////////////////////////////////////////// draw/draw_line.c //

/**
 * Draws a line from point 0 to point 1 onto img.
 *
 * @param	img
 * 		The image to be drawn onto.
 *
 * @param	p0
 * 		Coordinates of point of origin.
 *
 * @param	p1
 * 		Coordinates of the end point.
 */
void	draw_line(mlx_image_t *img, t_vec2i p0, t_vec2i p1, uint32_t color);

////////////////////////////////////////////////////// draw/image_to_image.c //

/**
 * Draws image onto another image at the given coordinates.
 *
 * @param	dst
 * 		Image to be drawn onto.
 *
 * @param	src
 * 		Image to be drawn.
 *
 * @param	x
 * 		X offset.
 *
 * @param	y
 * 		Y offset.
 */
void	img_to_img(mlx_image_t *dst, mlx_image_t *src, int32_t x, int32_t y);

//////////////////////////////////////////////////////////////// draw/rect.h //

/**
 * Function to create a rectangle.
 *
 * @param	x
 * 		X coordinate of the top left corner.
 *
 * @param	y
 * 		Y coordinate of the top left corner.
 *
 * @param	w
 * 		Width.
 *
 * @param	h
 * 		Height.
 *
 * @return
 * 		The rectangle.	
 */
t_rect	new_rect(int32_t x, int32_t y, uint32_t w, uint32_t h);

#endif
