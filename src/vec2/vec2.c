/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:16:33 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 12:04:37 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vec2.h"
#include <math.h>

void	vec2i_assign(t_vec2i *left, const t_vec2i *right)
{
	left->x = right->x;
	left->y = right->y;
}

void	vec2i_trunc(t_vec2i *left, const t_vec2 *right)
{
	left->x = (int32_t) right->x;
	left->y = (int32_t) right->y;
}

void	vec2_assign(t_vec2 *left, const t_vec2 *right)
{
	left->x = right->x;
	left->y = right->y;
}

void	vec2_sum(t_vec2 *left, const t_vec2 *right)
{
	left->x += right->x;
	left->y += right->y;
}

void	vec2_diff(t_vec2 *left, const t_vec2 *right)
{
	left->x -= right->x;
	left->y -= right->y;
}
