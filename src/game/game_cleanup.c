/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:29:08 by juaho             #+#    #+#             */
/*   Updated: 2025/07/23 19:50:58 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"

void	game_cleanup(t_game *game)
{
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->minimap)
		mlx_delete_image(game->mlx, game->minimap);
	if (game->map_img)
		mlx_delete_image(game->mlx, game->map_img);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map);
}
