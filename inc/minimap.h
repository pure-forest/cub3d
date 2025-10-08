/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:01:59 by ydeng             #+#    #+#             */
/*   Updated: 2025/07/30 14:49:36 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../inc/game.h"
# include "../libft/libft.h"

//////////////////////////////////////////////////// minimap/get_map_image.c //

/**
 * Generate an image based on the map grid. The image will be heap allocated
 * and needs to be freed by the user like all other images.
 *
 * @param	game
 * 		The game struct containing the map and all other necessary information.
 *
 * @return
 * 		Returns a pointer to a new mlx_image_t struct or NULL if the image
 * 		creation fails.
 */
mlx_image_t	*get_map_image(t_game *game);

/**
 * Updates the minimap image to reflect the present gamestate, mainly the
 * player position.
 *
 * @param	game
 * 		The game struct.
 */
void		update_minimap(t_game *game);

#endif
