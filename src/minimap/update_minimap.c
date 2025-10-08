/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:34:15 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 15:41:26 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include "../../inc/minimap.h"
#include "../../inc/defs.h"
#include "../../inc/draw.h"
#include "../../inc/raycasting.h"
#include <stdio.h>

static void	draw_minimap_and_player(t_game *game, t_vec2i *mm_ppos);
static void	draw_rays(t_game *game, t_vec2i *offset);

void	update_minimap(t_game *game)
{
	t_vec2i	mm_ppos;

	mm_ppos.x = (int32_t)(game->player.pos.x * TILE_SIZE);
	mm_ppos.y = (int32_t)(game->player.pos.y * TILE_SIZE);
	draw_minimap_and_player(game, &mm_ppos);
}

static void	draw_minimap_and_player(t_game *game, t_vec2i *mm_ppos)
{
	const uint32_t	p2 = PLAYER_SIZE / 2;
	t_vec2i			offset;
	t_rect			p_box;

	p_box = new_rect(MINIMAP_WIDTH / 2.0 - p2, MINIMAP_HEIGHT / 2.0 - p2,
			PLAYER_SIZE, PLAYER_SIZE);
	fill_image(game->minimap, MINIMAP_BG_CLR);
	offset.x = (int32_t) mm_ppos->x - game->minimap->width / 2;
	offset.y = (int32_t) mm_ppos->y - game->minimap->height / 2;
	img_to_img(game->minimap, game->map_img, -offset.x, -offset.y);
	draw_rect(game->minimap, &p_box, MINIMAP_PLAYER_CLR);
	draw_rays(game, &offset);
}

static void	draw_rays(t_game *game, t_vec2i *offset)
{
	t_vec2i		mm_center;
	t_vec2i		mm_ray_end;
	uint32_t	i;

	mm_center.x = MINIMAP_WIDTH / 2;
	mm_center.y = MINIMAP_HEIGHT / 2;
	i = 0;
	while (i < WIDTH)
	{
		mm_ray_end.x = game->ray_data[i].end.x * TILE_SIZE - offset->x;
		mm_ray_end.y = game->ray_data[i].end.y * TILE_SIZE - offset->y;
		draw_line(game->minimap, mm_center, mm_ray_end, MINIMAP_RAY_CLR);
		i++;
	}
}
