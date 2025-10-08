/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:19:52 by juaho             #+#    #+#             */
/*   Updated: 2025/07/30 12:06:41 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H
# include <stdint.h>

/**
 * 2-dimensional vector with floating-point (double) components x and y.
 *
 * @param	x	X component.
 * @param	y	Y component.
 */
typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

/**
 * 2-dimensional vector with integer components x and y.
 *
 * @param	x	X component.
 * @param	y	Y component.
 */
typedef struct s_vec2i
{
	int32_t	x;
	int32_t	y;
}	t_vec2i;

/**
 * Assigns the x and y of the right vector to the left vector.
 *
 * @param	left
 * 		Vector to be assigned to.
 *
 * @param	right
 * 		Vector to be assigned from.
 */
void	vec2i_assign(t_vec2i *left, const t_vec2i *right);

/**
 * Assigns the x and y of the right vec2 to the left vec2i truncating the
 * decimal parts.
 *
 * @param	left
 * 		The integral vector to be assigned to.
 *
 * @param	right
 * 		The floating point vector that that gets truncated.
 */
void	vec2i_trunc(t_vec2i *left, const t_vec2 *right);

/**
 * Assigns the x and y of the right vector to the left vector.
 *
 * @param	left
 * 		Vector to be assigned to.
 *
 * @param	right
 * 		Vector to be assigned from.
 */
void	vec2_assign(t_vec2 *left, const t_vec2 *right);

/**
 * Adds the x and y of the right vector to the left vector.
 *
 * @param	left
 * 		Vector where the sum is assigned to.
 *
 * @param	right
 * 		Right-hand side of the calculation.
 */
void	vec2_sum(t_vec2 *left, const t_vec2 *right);

/**
 * Subtracts the x and y of the right vector from the left vector.
 *
 * @param	left
 * 		Vector where the difference is assigned to.
 *
 * @param	right
 * 		Right-hand side of the calculation.
 */
void	vec2_diff(t_vec2 *left, const t_vec2 *right);

#endif
