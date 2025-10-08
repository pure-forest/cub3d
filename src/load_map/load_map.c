/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:12:29 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:35:14 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../inc/errors.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

static int32_t	open_map_file(const char *path);

bool	load_map(t_map *map, const char *path)
{
	t_map_data	data;
	int32_t		fd;
	char		*line;

	fd = open_map_file(path);
	if (fd < 0)
		return (false);
	ft_bzero(&data, sizeof(t_map_data));
	if (!parse_assets(&line, &data, fd))
	{
		close (fd);
		return (false);
	}
	if (!parse_grid(&line, map, fd))
	{
		close (fd);
		return (false);
	}
	close (fd);
	if (!load_assets(map, &data))
		return (false);
	if (!is_valid_map(map))
		return (false);
	return (true);
}

static int32_t	open_map_file(const char *path)
{
	int32_t	fd;

	if (!check_suffix(path, ".cub"))
	{
		print_error("Map file has incorrect suffix (should be '.cub')", NULL);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error("Can't open file", path);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	return (fd);
}
