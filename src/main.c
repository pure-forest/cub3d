/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:29:08 by juaho             #+#    #+#             */
/*   Updated: 2025/07/23 19:09:32 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"
#include "../inc/game.h"

int	main(int ac, char **av)
{
	t_map	map;
	t_game	game;

	if (ac != 2)
		return (2);
	if (!load_map(&map, av[1]))
		return (1);
	if (!game_init(&game, &map))
	{
		game_cleanup(&game);
		return (1);
	}
	mlx_loop(game.mlx);
	game_cleanup(&game);
	return (0);
}
