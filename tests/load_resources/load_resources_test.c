/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_resources_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:23:10 by juaho             #+#    #+#             */
/*   Updated: 2025/07/14 13:02:55 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/color.h"
#include <stdio.h>
#include <stdbool.h>

static char *boolstr(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static void	print_colors(t_map *map)
{
	printf("Floor:   R %3d\tG %3d\tB %3d\tA %3d\n",
			get_color_channel(map->floor_color, 'r'),
			get_color_channel(map->floor_color, 'g'),
			get_color_channel(map->floor_color, 'b'),
			get_color_channel(map->floor_color, 'a'));
	printf("Ceiling: R %3d\tG %3d\tB %3d\tA %3d\n",
			get_color_channel(map->ceiling_color, 'r'),
			get_color_channel(map->ceiling_color, 'g'),
			get_color_channel(map->ceiling_color, 'b'),
			get_color_channel(map->ceiling_color, 'a'));
}

static bool	test(t_map_data *data, const char *description, bool expected)
{
	static int	testno;
	bool		res;
	t_map		map;

	testno++;
	printf("\n\033[01;46m=== TEST %d ===\033[0m\n", testno);
	printf("\033[34mtest description: %s\033[0m\n", description);

	printf("\033[91m\n");
	init_map(&map);
	res = load_resources(&map, data);
	printf("\033[0m");
	print_colors(&map);
	printf("\033[01;33mOutput:\033[0m %s\n", boolstr(res));
	printf("\033[01;93mExpected:\033[0m %s\n", boolstr(expected));
	if (res == expected)
		printf("✅ \033[01;92mMATCH\033[0m\n");
	else
		printf("❌ \033[01;91mMISMATCH\033[0m\n");
	free_map(&map);
	return (res == expected);
}

int main()
{
	t_map_data	data;
	uint8_t		passed = 0;
	uint8_t		total = 0;

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png";
	data.south_wall_tex_path = "../../resources/south.png";
	data.west_wall_tex_path = "../../resources/west.png";
	data.east_wall_tex_path = "../../resources/east.png";
	data.floor_color_string = "255,0,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "all normal", true);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png ";
	data.south_wall_tex_path = "../../resources/south.png	";
	data.west_wall_tex_path = "../../resources/west.png.";
	data.east_wall_tex_path = "../../resources/east.pngg";
	data.floor_color_string = "255,0,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "stuff after suffix", false);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.gif";
	data.south_wall_tex_path = "../../resources/south.bmp";
	data.west_wall_tex_path = "../../resources/west.tiff";
	data.east_wall_tex_path = "../../resources/east.p";
	data.floor_color_string = "255,0,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "wrong suffix", false);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png";
	data.south_wall_tex_path = "../../resources/south.png";
	data.west_wall_tex_path = "../../resources/west.png";
	data.east_wall_tex_path = "../../resources/east.png";
	data.floor_color_string = "300,0,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "color channel goes over 255", false);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png";
	data.south_wall_tex_path = "../../resources/south.png";
	data.west_wall_tex_path = "../../resources/west.png";
	data.east_wall_tex_path = "../../resources/east.png";
	data.floor_color_string = "-1,0,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "negative colors", false);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png";
	data.south_wall_tex_path = "../../resources/south.png";
	data.west_wall_tex_path = "../../resources/west.png";
	data.east_wall_tex_path = "../../resources/east.png";
	data.floor_color_string = "0,5000000000,0";
	data.ceiling_color_string = "100,100,100";

	total++;
	passed += test(&data, "color overflow", false);

	init_map_data(&data);
	data.north_wall_tex_path = "../../resources/north.png";
	data.south_wall_tex_path = "../../resources/south.png";
	data.west_wall_tex_path = "../../resources/west.png";
	data.east_wall_tex_path = "../../resources/east.png";
	data.floor_color_string = "255, 0, 0";
	data.ceiling_color_string = "100 100 100";

	total++;
	passed += test(&data, "different color format", true);

	printf("\n\033[01;93mTESTS PASSED: %u/%u\033[0m\n", passed, total);
	return (passed - total);
}
