/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:08:52 by juaho             #+#    #+#             */
/*   Updated: 2025/07/14 13:14:27 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../inc/map.h"

static void	print_map(t_map *map)
{
	for (int32_t y = 0; y < map->h; y++)
		printf("\033[100m%*.*s\033[0m\n", map->w, map->w, map->grid + y * map->w);
}

static char *boolstr(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static bool	test(t_map *map, const char *description, bool expected)
{
	static int	testno;
	bool		res;

	testno++;
	printf("\n\033[01;46m=== TEST %d ===\033[0m\n", testno);
	printf("\033[34mtest description: %s\033[0m\n\n", description);

	print_map(map);

	printf("\033[91m\n");
	res = is_valid_map(map);
	printf("\033[0m");
	printf("\033[01;33mOutput:\033[0m %s\n", boolstr(res));
	printf("\033[01;93mExpected:\033[0m %s\n", boolstr(expected));
	if (res == expected)
		printf("✅ \033[01;92mMATCH\033[0m\n");
	else
		printf("❌ \033[01;91mMISMATCH\033[0m\n");
	return (res == expected);
}

bool	is_valid_map(t_map *map);

int main()
{
	uint8_t	total = 7;
	uint8_t	passed = 0;
	t_map	map;

	map.w = 5;
	map.h = 5;

	map.grid = \
		"11111" \
		"10001" \
		"1S001" \
		"10001" \
		"11111";

	passed += test(&map, "regular proper box", true);

	map.grid = \
		"1111 " \
		"10001" \
		"10N01" \
		"10001" \
		"11111";

	passed += test(&map, "top right corner missing", false);

	map.grid = \
		"11111" \
		"10001" \
		"10 01" \
		"10W01" \
		"11111";

	passed += test(&map, "empty space inside the box", false);

	map.grid = \
		"1111 " \
		"1001 " \
		"10010" \
		"1E01 " \
		"1111 ";

	passed += test(&map, "floor outside the box in the void", false);

	map.grid = \
		"11111" \
		"1N001" \
		"10111" \
		"101  " \
		"111  ";

	passed += test(&map, "proper map, different shape", false);

	map.grid = \
		"11111" \
		"10001" \
		"10111" \
		"101  " \
		"111  ";

	passed += test(&map, "player spawn missing", false);

	map.grid = \
		"11111" \
		"100S1" \
		"10111" \
		"1W1  " \
		"111  ";

	passed += test(&map, "multiple player spawns", false);

	printf("\n\033[01;93mTESTS PASSED: %u/%u\033[0m\n", passed, total);
	return (passed - total);
}
