/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:05:48 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 11:22:10 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../inc/draw.h"
#include <stdint.h>

void	fill_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_rect(mlx_image_t *img, t_rect *rect, uint32_t color)
{
	const uint32_t	x1 = rect->x + rect->w;
	const uint32_t	y1 = rect->y + rect->h;
	uint32_t		x;
	uint32_t		y;

	y = rect->y;
	while (y < y1)
	{
		x = rect->x;
		while (x < x1)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
