/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:50:08 by juaho             #+#    #+#             */
/*   Updated: 2025/08/06 19:17:39 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/errors.h"
#include "../../inc/game.h"
#include "../../inc/minimap.h"
#include "../../inc/hooks.h"
#include "../../inc/defs.h"
#include <math.h>

static bool	init_minimap(t_game *game);
static void	init_player(t_game *game);
static void	get_player_pos_and_angle(t_game *game, t_vec2i *pos, char c);
static void	init_hooks(t_game *game);

bool	game_init(t_game *game, t_map *map)
{
	ft_bzero(game, sizeof(t_game));
	game->map = map;
	game->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!game->mlx)
	{
		print_error("game_init", mlx_strerror(mlx_errno));
		return (false);
	}
	game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen)
	{
		print_error("game screen: mlx_new_image", mlx_strerror(mlx_errno));
		return (false);
	}
	init_player(game);
	if (!init_minimap(game))
		return (false);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	init_hooks(game);
	return (true);
}

static bool	init_minimap(t_game *game)
{
	game->minimap = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!game->minimap)
	{
		print_error("minimap: mlx_new_image", mlx_strerror(mlx_errno));
		return (false);
	}
	game->map_img = get_map_image(game);
	if (!game->map_img)
	{
		print_error("minimap: get_map_image", mlx_strerror(mlx_errno));
		return (false);
	}
	return (true);
}

static void	init_player(t_game *game)
{
	t_vec2i	pos;
	char	c;

	pos.y = 0;
	while (pos.y < (int32_t) game->map->h)
	{
		pos.x = 0;
		while (pos.x < (int32_t) game->map->w)
		{
			c = game->map->grid[pos.x + pos.y * game->map->w];
			if (c == 'E' || c == 'N' || c == 'W' || c == 'S')
			{
				get_player_pos_and_angle(game, &pos, c);
				return ;
			}
			pos.x++;
		}
		pos.y++;
	}
}

static void	get_player_pos_and_angle(t_game *game, t_vec2i *pos, char c)
{
	game->player.vel.x = 0;
	game->player.vel.y = 0;
	game->player.pos.x = (double) pos->x + 0.5;
	game->player.pos.y = (double) pos->y + 0.5;
	if (c == 'E')
		game->player.angle = 0;
	else if (c == 'S')
		game->player.angle = M_PI_2;
	else if (c == 'W')
		game->player.angle = M_PI;
	else if (c == 'N')
		game->player.angle = M_PI + M_PI_2;
	game->player.dir.x = cos(game->player.angle);
	game->player.dir.y = sin(game->player.angle);
}

static void	init_hooks(t_game *game)
{
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game->mlx, &loop_hook, game);
	mlx_cursor_hook(game->mlx, &cursor_hook, game);
	mlx_close_hook(game->mlx, &close_hook, game);
}
