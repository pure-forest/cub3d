/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:54:59 by juaho             #+#    #+#             */
/*   Updated: 2025/07/24 00:28:19 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include <stdint.h>
# include <stdbool.h>

/**
 * All the color functions are made to be compatible with the way mlx_put_pixel
 * handles the color channels. In the actual image pixel buffers of MLX42 the
 * color channels are not in RGBA order, but instead ARGB. So if you'd take 4
 * adjacent bytes from an images pixels array an treat that as a uint32_t, the
 * channels are going to be in wrong order for the format that mlx_put_pixel
 * expects... Hats off to them.
 */

////////////////////////////////////////////////////////////// color/color.c //

/**
 * Extracts 8bit number values for red, green and blue from given string and
 * stores the result in color.``
 *
 * @param	string
 * 		String to parse the color from.
 *
 * @param	color
 * 		Pointer to the color where the result is stored.
 *
 * @return
 * 		Returns false if the string doesn't have 3 numbers separated by
 * 		non-digits or one of the numbers is more than 255.
 */
bool		string_to_color(char *string, uint32_t *color);

/**
 * Get the component channel c from given color.
 *
 * @param	color
 * 		The color.
 *
 * @param	c
 * 		Character for the channel to get: 'r', 'g', 'b' or 'a' (red, green,
 * 		blue or alpha).
 */
uint8_t		get_color_channel(uint32_t color, char c);

/**
 * Combines given color channels into one 32bit integer.
 *
 * @param	r
 * 		Red channel.
 *
 * @param	g
 * 		Green channel.
 *
 * @param	b
 * 		Blue channel.
 *
 * @param	a
 * 		Alpha channel.
 *
 * @return
 * 		32bit integer representing the color.
 */
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif
