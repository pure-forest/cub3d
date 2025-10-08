/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:48:47 by juaho             #+#    #+#             */
/*   Updated: 2025/07/23 19:50:28 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include <stdlib.h>

void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	game_cleanup(game);
	exit(0);
}
