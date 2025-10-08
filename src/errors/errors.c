/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:14:28 by juaho             #+#    #+#             */
/*   Updated: 2025/08/04 15:31:48 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/errors.h"

void	print_error(const char *s1, const char *s2)
{
	char	buf[ERROR_MSG_MAX];

	buf[0] = '\0';
	ft_strlcat(buf, "Error\n", ERROR_MSG_MAX);
	ft_strlcat(buf, s1, ERROR_MSG_MAX);
	if (s2)
	{
		ft_strlcat(buf, ": ", ERROR_MSG_MAX);
		ft_strlcat(buf, s2, ERROR_MSG_MAX);
	}
	ft_putendl_fd(buf, 2);
}
