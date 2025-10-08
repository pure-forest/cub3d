/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:18:48 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 15:39:04 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../inc/vec2.h"
#include "../../libft/libft.h"
#include <stdint.h>

static void	delta_and_step(t_vec2i *d, t_vec2i *s, t_vec2i *p0, t_vec2i *p1);
static void	put_pixel(mlx_image_t *img, int32_t	x, int32_t y, uint32_t color);

void	draw_line(mlx_image_t *img, t_vec2i p0, t_vec2i p1, uint32_t color)
{
	t_vec2i	delta;
	t_vec2i	step;
	int64_t	error;
	int64_t	error2;

	delta_and_step(&delta, &step, &p0, &p1);
	error = delta.x - delta.y;
	while (1)
	{
		put_pixel(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			return ;
		error2 = error << 1;
		if (error2 >= -delta.y)
		{
			p0.x += step.x;
			error += -delta.y;
		}
		if (error2 <= delta.x)
		{
			p0.y += step.y;
			error += delta.x;
		}
	}
}

static void	delta_and_step(t_vec2i *d, t_vec2i *s, t_vec2i *p0, t_vec2i *p1)
{
	d->x = ft_abs(p0->x - p1->x);
	d->y = ft_abs(p0->y - p1->y);
	if (p0->x > p1->x)
		s->x = -1;
	else
		s->x = 1;
	if (p0->y > p1->y)
		s->y = -1;
	else
		s->y = 1;
}

static void	put_pixel(mlx_image_t *img, int32_t	x, int32_t y, uint32_t color)
{
	if (x < 0 || x >= (int32_t) img->width)
		return ;
	if (y < 0 || y >= (int32_t) img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}
