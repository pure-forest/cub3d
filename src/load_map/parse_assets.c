/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:39:17 by juaho             #+#    #+#             */
/*   Updated: 2025/08/07 17:47:51 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../inc/errors.h"
#include "../../inc/map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

static void		error_map_file_incomplete(t_map_data *data);
static uint8_t	process_asset(char *line, t_map_data *data);
static uint8_t	feed_line_to_map_data(char *line, t_map_data *data);
static uint8_t	extract_line_to_map_data(char *line, char **field);

bool	parse_assets(char **line, t_map_data *data, int32_t fd)
{
	uint8_t	ret;

	while (true)
	{
		*line = get_next_line(fd);
		if (!*line)
		{
			if (errno)
				print_error("get_next_line", strerror(errno));
			else
				error_map_file_incomplete(data);
			return (false);
		}
		ret = process_asset(*line, data);
		if (ret == NOT_AN_ASSET)
			break ;
		free(*line);
		if (ret)
			return (false);
	}
	return (true);
}

static void	error_map_file_incomplete(t_map_data *data)
{
	print_error("Map file incomplete.", NULL);
	if (!data->north_wall_str)
		ft_putendl_fd("Missing north wall asset.", 2);
	if (!data->east_wall_str)
		ft_putendl_fd("Missing east wall asset.", 2);
	if (!data->south_wall_str)
		ft_putendl_fd("Missing south wall asset.", 2);
	if (!data->west_wall_str)
		ft_putendl_fd("Missing west wall asset.", 2);
	if (!data->floor_str)
		ft_putendl_fd("Missing floor asset.", 2);
	if (!data->ceiling_str)
		ft_putendl_fd("Missing ceiling asset.", 2);
}

static uint8_t	process_asset(char *line, t_map_data *data)
{
	uint8_t	ret;

	ret = feed_line_to_map_data(line, data);
	if (ret == ERR_UNEXPECTED_LINE)
	{
		print_error("Unexpected line", line);
		return (ret);
	}
	if (ret == ERR_FIELD_OVERWRITE)
	{
		print_error("Multiple definitions of asset", line);
		return (ret);
	}
	if (ret == ERR_MALLOC_FAIL)
	{
		print_error("parse_assets malloc failure", strerror(errno));
		return (ret);
	}
	if (ret == NOT_AN_ASSET && map_data_has_empty_fields(data))
	{
		error_map_file_incomplete(data);
		return (ret);
	}
	return (ret);
}

static uint8_t	feed_line_to_map_data(char *line, t_map_data *data)
{
	uint8_t	ret;

	if (line[0] == '\n')
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		ret = (extract_line_to_map_data(line + 2, &data->north_wall_str));
	else if (!ft_strncmp(line, "SO ", 3))
		ret = (extract_line_to_map_data(line + 2, &data->south_wall_str));
	else if (!ft_strncmp(line, "WE ", 3))
		ret = (extract_line_to_map_data(line + 2, &data->west_wall_str));
	else if (!ft_strncmp(line, "EA ", 3))
		ret = (extract_line_to_map_data(line + 2, &data->east_wall_str));
	else if (!ft_strncmp(line, "F ", 2))
		ret = (extract_line_to_map_data(line + 1, &data->floor_str));
	else if (!ft_strncmp(line, "C ", 2))
		ret = (extract_line_to_map_data(line + 1, &data->ceiling_str));
	else if (map_data_has_empty_fields(data))
		return (ERR_UNEXPECTED_LINE);
	else
		return (NOT_AN_ASSET);
	return (ret);
}

static uint8_t	extract_line_to_map_data(char *line, char **field)
{
	uint32_t	start;
	uint32_t	len;

	start = 0;
	len = 0;
	if (*field)
		return (ERR_FIELD_OVERWRITE);
	while (line[start] && ft_isspace(line[start]))
		start++;
	while (line[start + len] && line[start + len] != '\n')
		len++;
	if (len > 1)
		while (ft_isspace(line[start + len - 1]))
			len--;
	*field = (char *) malloc(sizeof(char) * (len + 1));
	if (!*field)
		return (ERR_MALLOC_FAIL);
	ft_memcpy(*field, &line[start], len);
	(*field)[len] = '\0';
	return (0);
}
