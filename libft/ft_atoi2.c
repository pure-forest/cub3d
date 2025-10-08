/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:38:11 by juaho             #+#    #+#             */
/*   Updated: 2025/02/05 16:00:54 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static	int	atoi2_inner(const char *a, int *i, int neg)
{
	long	num;
	int		overflow;

	num = 0;
	overflow = 0;
	while (*a >= '0' && *a <= '9')
	{
		num *= 10;
		if (neg)
			num -= *a - '0';
		else
			num += *a - '0';
		if (!overflow && (num > INT_MAX || num < INT_MIN))
			overflow = 1;
		a++;
	}
	*i = num;
	return (overflow);
}

int	ft_atoi2(const char *a, int *i)
{
	int		neg;

	neg = 0;
	while (ft_isspace(*a))
		a++;
	if (*a == '-' || *a == '+')
	{
		if (*a == '-')
			neg = 1;
		a++;
	}
	return (atoi2_inner(a, i, neg));
}
