/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:44:58 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 18:04:14 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdint.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# define ERR_UNEXPECTED_LINE 10
# define ERR_FIELD_OVERWRITE 20
# define ERR_MALLOC_FAIL 30
# define NOT_AN_ASSET 40

/**
 * A struct that holds either a texture or a solid color.
 *
 * @param	is_texture	Tells which type the union holds.
 * @param	asset		Stores either an mlx_texture_t or a solid color.
 */
typedef struct s_texture
{
	bool	is_texture;
	union
	{
		mlx_texture_t	*texture;
		uint32_t		color;
	}	u_asset;
}	t_texture;

/**
 * A struct storing the maps grid, width and height, but also all the wall
 * textures and the ceiling and floor colors. Initialized with init_map() and
 * should be freed with free_map() in the end.
 *
 * @param	north_wall_tex	North wall texture / color.
 * @param	east_wall_tex	East wall texture / color.
 * @param	south_wall_tex	South wall texture / color.
 * @param	west_wall_tex	West wall texture / color.
 * @param	floor_color		Floor texture / color.
 * @param	ceiling_color	Ceiling texture / color.
 * @param	w				Width of the map grid.
 * @param	h				Height of the map grid.
 * @param	grid			The map grid, stored as a one-dimensional array.
 */
typedef struct s_map
{
	t_texture		north_wall;
	t_texture		east_wall;
	t_texture		south_wall;
	t_texture		west_wall;
	t_texture		floor;
	t_texture		ceiling;
	uint8_t			w;
	uint8_t			h;
	char			*grid;
}	t_map;

/**
 * A temporary storage for parsed info from the maps file that is used in
 * loading the map. Initialized with init_map_data() and should be freed with
 * free_map_data() in the end.
 *
 * @param	north_wall_str	North wall texture path / color.
 * @param	east_wall_str	East wall texture path / color.
 * @param	south_wall_str	South wall texture path / color.
 * @param	west_wall_str	West wall texture path / color.
 * @param	floor_str		Floor texture path / color.
 * @param	ceiling_str		Ceiling texture path / color.
 */
typedef struct s_map_data
{
	char	*north_wall_str;
	char	*east_wall_str;
	char	*south_wall_str;
	char	*west_wall_str;
	char	*floor_str;
	char	*ceiling_str;
}	t_map_data;

/////////////////////////////////////// load_map/error_map_file_incomplete.c //

/**
 * Checks if the t_map_data struct has any fields that are still NULL.
 *
 * @param	data
 * 		The map data struct to check.
 *
 * @return
 * 		True if any of the fields are NULL, false otherwise.
 */
bool	map_data_has_empty_fields(t_map_data *data);

///////////////////////////////////////////////////// load_map/load_assets.c //

/**
 * Loads colors and textures collected into map_data into the map struct.
 * Validates the data while loading.
 *
 * @param	map
 * 		The map that will hold the mlx_texture_t 's and parsed colors.
 *
 * @param	data
 * 		The data struct with the texture paths and the color strings.
 *
 * @return
 * 		Returns true if everything goes right. False if something goes wrong
 * 		in the validation or opening files fails.
 */
bool	load_assets(t_map *map, t_map_data *data);

//////////////////////////////////////////////////////// load_map/load_map.c //

/**
 * Loads map from given path into the given struct map.
 *
 * @param	map
 * 		The map struct where the map will be loaded into.
 *
 * @param	path
 * 		Path of the map file to load.
 *
 * @return
 * 		Returns true on success, false on failure.
 */
bool	load_map(t_map *map, const char *path);

/////////////////////////////////////////////////////// load_map/map_utils.c //

/**
 * Frees all allocations inside the map struct.
 *
 * @param	map
 * 		The map struct.
 */
void	free_map(t_map *map);

/**
 * Frees the heap allocated strings stored in the map data struct. Does NOT free
 * the map data struct itself!
 *
 * @param	data
 * 		Pointer to map data struct.
 */
void	free_map_data(t_map_data *data);

/**
 * Checks the suffix of a string.
 *
 * @param	string
 * 		The string to check.
 *
 * @param	suffix
 * 		The ending to search for
 *
 * @return
 * 		If the string ends with the suffix, true is returned. Otherwise false.
 */
bool	check_suffix(const char *string, const char *suffix);

//////////////////////////////////////////////////// load_map/validate_map.c //

/**
 * Checks the maps grid for valid characters (0, 1, ' ', N, S, W, E) and also
 * checks that there are no zeros in contact with the void.
 *
 * @param	map
 * 		The map.
 *
 * @return
 * 		Returns true if the map is deemed valid.
 */
bool	is_valid_map(t_map *map);

//////////////////////////////////////////////////// load_map/parse_assets.c //

/**
 * Extracts the texture paths and color values of walls, floor and ceiling from
 * the map file and stores it into data.
 *
 * @param	line
 * 		A pointer that holds the last line we read from the fd. When reading a
 * 		line that isn't an asset anymore, the function stops reading and passes
 * 		the last read line to the parse_grid(), so it stops on the first line of
 * 		the map and that's where parse_grid picks up.
 *
 * @param	data
 * 		Struct with textures paths and color values.
 *
 * @param	fd
 * 		The map file's file descriptor.
 *
 * @return
 * 		Returns true if all the necessary assets are found, in the correct
 * 		format, before the map grid starts.
 */
bool	parse_assets(char **line, t_map_data *data, int32_t fd);

///////////////////////////////////////////////////// load_map/parse_grid.c //

/**
 * Extracts the map grid from the map file, padding it with spaces to make the
 * map grid a perfect rectangle in case some lines of the grid have different
 * widths. The first line it starts with is the line that stops parse_assests.
 *
 * @param	line
 * 		The last line read by parse_assets(), so the first line of the grid.
 *
 * @param	map
 * 		The map struct that will store the grid.
 *
 * @param	fd
 * 		The map files file descriptor.
 *
 * @return
 * 		Returns false if a heap allocation fails. Otherwise true.
 */
bool	parse_grid(char **line, t_map *map, int32_t fd);

#endif
