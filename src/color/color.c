/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeng <ydeng@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:40:35 by juaho             #+#    #+#             */
/*   Updated: 2025/07/16 10:45:19 by ydeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <stdbool.h>

bool	string_to_color(char *string, uint32_t *color)
{
	uint32_t	temp;
	uint8_t		i;

	i = 0;
	while (i++ < 3)
	{
		if (!ft_isdigit(*string))
			return (false);
		temp = 0;
		while (ft_isdigit(*string))
		{
			temp *= 10;
			temp += *string - '0';
			if (temp > 255)
				return (false);
			string++;
		}
		while (*string && !ft_isdigit(*string))
			string++;
		*color = (*color + temp) << 8;
	}
	*color += 255;
	return (true);
}

uint8_t	get_color_channel(uint32_t color, char c)
{
	if (c == 'r')
		return (color >> 24);
	if (c == 'g')
		return ((color >> 16) % 256);
	if (c == 'b')
		return ((color >> 8) % 256);
	if (c == 'a')
		return (color % 256);
	return (0);
}

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}
