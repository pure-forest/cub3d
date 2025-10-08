/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_img_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:27:15 by juaho             #+#    #+#             */
/*   Updated: 2025/07/23 22:41:16 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../inc/rect.h"
#include "../../inc/minimap.h"
#include "../../inc/color.h"
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct	s_data
{
	mlx_t		*mlx;
	mlx_image_t	*screen;
	mlx_image_t	*frodo;
	mlx_image_t	*map;
	int32_t		x_off;
	int32_t		y_off;
}	t_data;

void	key_hook(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->x_off -= 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->x_off += 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->y_off -= 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->y_off += 2;

	t_rect *bgbox = new_rect(0, 0, WIDTH, HEIGHT);
	draw_rectangle(data->screen, bgbox, get_rgba(255, 0, 255, 255));
	free(bgbox);
	img_to_img(data->screen, data->map, -data->x_off, -data->y_off);
	img_to_img(data->screen, data->frodo,
			data->screen->width / 2 - data->frodo->width / 2,
			data->screen->height / 2 - data->frodo->height / 2);
}

int main()
{
	t_data			data;
	mlx_texture_t	*frodo;
	mlx_texture_t	*map;

	data.mlx = mlx_init(WIDTH, HEIGHT, "image2image test", false);
	if (!data.mlx)
		return (1);
	frodo = mlx_load_png("frodo.png");
	if (!frodo)
		return (1);
	map = mlx_load_png("me.png");
	if (!map)
		return (1);
	data.frodo = mlx_texture_to_image(data.mlx, frodo);
	if (!data.frodo)
		return (1);
	data.map = mlx_texture_to_image(data.mlx, map);
	if (!data.map)
		return (1);
	data.screen = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_delete_texture(frodo);
	mlx_delete_texture(map);
	data.x_off = data.map->width / 2;
	data.y_off = data.map->height / 2;

	mlx_image_to_window(data.mlx, data.screen, 0, 0);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	exit(0);
}
