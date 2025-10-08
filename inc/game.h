/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:34:18 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 16:54:19 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../inc/map.h"
# include "../inc/defs.h"
# include "../inc/vec2.h"
# include "../inc/raycasting.h"
# include "../inc/render.h"
# include <stdbool.h>

/**
 * Game object, has 3 vectors: position, direction and velocity. Also a double
 * for angle.
 *
 * @param	pos		A t_vec2 for position.
 * @param	dir		A t_vec2 for facing direction.
 * @param	vel		A t_vec2 for velocity.
 * @param	angle	The angle of the facing direction in rad.
 */
typedef struct s_gobj
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	vel;
	double	angle;
}	t_gobj;

/**
 * Struct that holds all the game resources and data for easy access.
 * Initialized with game_init(). Has to be freed with game_cleanup() in the end.
 *
 * @param	ray_data	The cast rays will be stored in this array.
 * @param	player		A t_gobj with the player's position, angle and speed.
 * @param	screen		The main game display image.
 * @param	minimap		The image for the minimap display.
 * @param	map_img		An image of the whole game map.
 * @param	mlx			The mlx_t struct.
 * @param	map			The game map itself.
 */
typedef struct s_game
{
	t_ray		ray_data[WIDTH];
	t_gobj		player;
	mlx_image_t	*screen;
	mlx_image_t	*minimap;
	mlx_image_t	*map_img;
	mlx_t		*mlx;
	t_map		*map;
}	t_game;

/////////////////////////////////////////////////////////// game/game_init.c //

/**
 * Initializes the game struct. Sets up MLX, the screen and minimap images and
 * the player position.
 *
 * @param	game
 * 		The game struct to be initialized.
 *
 * @param	map
 * 		Map succesfully loaded with load_map().
 *
 * @return
 * 		Returns false if some of the mlx functions fail, otherwise true.
 */
bool	game_init(t_game *game, t_map *map);

//////////////////////////////////////////////////////// game/game_cleanup.c //

/**
 * Cleans up mlx, all images and the map. Does NOT free the game struct itself!
 *
 * @param	game
 * 		The game struct.
 */
void	game_cleanup(t_game *game);

#endif
