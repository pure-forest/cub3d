/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:59:35 by juaho             #+#    #+#             */
/*   Updated: 2025/07/15 15:19:36 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				dif;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	dif = 0;
	while (n > 0)
	{
		dif = *us1 - *us2;
		if (!*us1 || !*us2)
			break ;
		if (dif != 0)
			break ;
		us1++;
		us2++;
		n--;
	}
	return (dif);
}
