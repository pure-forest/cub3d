/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:01:43 by ydeng             #+#    #+#             */
/*   Updated: 2025/08/06 20:23:31 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minimap.h"
#include "../../inc/draw.h"
#include "../../inc/defs.h"

static void	draw_tile(mlx_image_t *img, t_rect *tile, char c);

mlx_image_t	*get_map_image(t_game *game)
{
	mlx_image_t	*image;
	t_rect		rect;
	uint32_t	x;
	uint32_t	y;

	image = mlx_new_image(game->mlx, game->map->w * TILE_SIZE,
			game->map->h * TILE_SIZE);
	if (!image)
		return (NULL);
	rect = new_rect(0, 0, TILE_SIZE, TILE_SIZE);
	y = 0;
	while (y * TILE_SIZE < image->height)
	{
		x = 0;
		while (x * TILE_SIZE < image->width)
		{
			rect.x = x * TILE_SIZE;
			rect.y = y * TILE_SIZE;
			draw_tile(image, &rect, game->map->grid[x + y * game->map->w]);
			x++;
		}
		y++;
	}
	return (image);
}

static void	draw_tile(mlx_image_t *img, t_rect *tile, char c)
{
	int32_t	color;

	if (c == '1')
		color = MINIMAP_WALL_CLR;
	else if (c == ' ')
		color = MINIMAP_BG_CLR;
	else
		color = MINIMAP_FLOOR_CLR;
	draw_rect(img, tile, color);
}
