/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:06:39 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 14:50:16 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include <stdint.h>

void	img_to_img(mlx_image_t *dst, mlx_image_t *src, int32_t x, int32_t y)
{
	uint32_t	*dst_pix;
	uint32_t	*src_pix;
	int32_t		x_i;
	int32_t		y_i;

	dst_pix = (uint32_t *) dst->pixels;
	src_pix = (uint32_t *) src->pixels;
	y_i = 0;
	if (y < 0)
		y_i -= y;
	while (y_i < (int32_t) src->height && y + y_i < (int32_t) dst->height)
	{
		x_i = 0;
		if (x < 0)
			x_i -= x;
		while (x_i < (int32_t) src->width && x + x_i < (int32_t) dst->width)
		{
			dst_pix[x + x_i + (y + y_i) * dst->width]
				= src_pix[x_i + y_i * src->width];
			x_i++;
		}
		y_i++;
	}
}
