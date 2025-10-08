/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:19:45 by juaho             #+#    #+#             */
/*   Updated: 2025/08/02 13:30:49 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# define ERROR_MSG_MAX 1024

///////////////////////////////////////////////////////////// errors/error.c //

/**
 * Displays an error message in stderr with a fixed "Error" followed by a
 * newline. The error message can be given in two parts with s1 and s2. s2 can
 * be NULL.
 *
 * @param	s1
 * 		First part of the error message.
 *
 * @param	s2
 * 		Second part of the error message. Can be NULL.
 */
void	print_error(const char *s1, const char *s2);

#endif
