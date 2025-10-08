/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:51:58 by juaho             #+#    #+#             */
/*   Updated: 2025/07/22 12:51:39 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/map.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define ERROR_LOG "error_log"

t_map map;

static bool	test(const char *path, const char *description, bool expected,
												const char *expected_error);
static char *boolstr(bool b);
static bool	setup_error_logging(int32_t	*stderr_backup_fd);
static bool	get_error_log(int32_t stderr_backup_fd, char **error_message);

int main()
{
	int		passed = 0;
	int		total = 0;

	total++;
	passed += test("maps/good1", "good", true, "");

	total++;
	passed += test("maps/good2", "good, but stuff in different order", true, "");

	total++;
	passed += test("maps/good_weird_color",
			"good, but color formatting is ESOTERIC", true, "");

	total++;
	passed += test("maps/no_such_file", "map file doesn't exist", false,
			"Error\ncan't open file: maps/no_such_file\n");

	total++;
	passed += test("maps/no_map_grid", "file has no map grid", false, 
			"Error\nCouldn't load map grid\n");

	total++;
	passed += test("maps/empty", "empty file", false,
					"Error\n" \
					"map file incomplete\n" \
					"missing north wall texture\n" \
					"missing east wall texture\n" \
					"missing south wall texture\n" \
					"missing west wall texture\n" \
					"missing floor color\n" \
					"missing ceiling color\n");

	total++;
	passed += test("maps/bad_filenames", "bad filenames", false,
				"MLX42: LodePNG: failed to open file for reading\n" \
				"Error\n" \
				"texture loading failed: PNG file is invalid or corrupted\n");

	total++;
	passed += test("maps/bad_suffix", "bad suffix", false,
					"Error\n" \
					"incorrect suffix on texture paths\n");

	total++;
	passed += test("maps/bad_suffix2", "bad suffix 2", false,
					"Error\n" \
					"incorrect suffix on texture paths\n");

	total++;
	passed += test("maps/texture_under_grid", "texture is after the grid", false,
					"Error\ninvalid line in between map resources: 11111111\n\n");

	printf("\n\033[01;93mTESTS PASSED: %u/%u\033[0m\n", passed, total);
	return (passed - total);
}

static bool	test(const char *path, const char *description, bool expected,
												const char *expected_error)
{
	static int	testno;
	bool		return_value;
	bool		error_comparison;
	int32_t		stderr_backup_fd;
	char		*error_msg;

	testno++;
	init_map(&map);
	printf("\n\033[01;46m=== TEST %d ===\033[0m\n", testno);
	printf("\033[34mtest description: %s\033[0m\n", description);

	// error logging
	if (!setup_error_logging(&stderr_backup_fd))
		return (false);

	// THE FUNCTION
	return_value = load_map(&map, path);
	// ------------

	error_msg = NULL;
	if (!get_error_log(stderr_backup_fd, &error_msg))
	{
		perror("get_error_log failed");
		return (false);
	}

	// return value comparison
	printf("\n\033[01;61m- Return value -\033[0m\n");
	printf("\033[01;33mOutput:\033[0m %s\n\n", boolstr(return_value));
	printf("\033[01;93mExpected:\033[0m %s\n\n", boolstr(expected));
	if (return_value == expected)
		printf("✅ \033[01;92mMATCH\033[0m\n");
	else
		printf("❌ \033[01;91mMISMATCH\033[0m\n");

	// errors comparison
	printf("\n\033[01;61m- Errors -\033[0m\n");
	printf("\033[01;33mOutput:\033[0m %s\n", error_msg);
	printf("\033[01;93mExpected:\033[0m %s\n", expected_error);
	error_comparison = ft_strcmp(expected_error, error_msg) == 0;
	if (error_comparison)
		printf("✅ \033[01;92mMATCH\033[0m\n");
	else
		printf("❌ \033[01;91mMISMATCH\033[0m\n");

	free_map(&map);
	return (return_value == expected && error_comparison);
}

static char *boolstr(bool b)
{
	if (b)
		return ("true");
	return ("false");
}

static bool	setup_error_logging(int32_t	*stderr_backup_fd)
{
	*stderr_backup_fd = dup(STDERR_FILENO);
	if (*stderr_backup_fd < 0)
	{
		perror("setup_error_logging: dup");
		return (false);
	}
	int32_t	error_log_fd = open(ERROR_LOG, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (error_log_fd < 0)
	{
		perror("setup_error_logging: open");
		close(*stderr_backup_fd);
		return (false);
	}
	if (dup2(error_log_fd, STDERR_FILENO) < 0)
	{
		perror("setup_error_logging: dup2");
		close(*stderr_backup_fd);
		close(error_log_fd);
		unlink(ERROR_LOG);
		return (false);
	}
	close(error_log_fd);
	return (true);
}

static bool	get_error_log(int32_t stderr_backup_fd, char **error_message)
{
	char	error_buffer[2048];
	bool	ret;

	if (dup2(stderr_backup_fd, STDERR_FILENO) < 0)
	{
		perror("get_error_log: dup2");
		return (false);
	}
	close(stderr_backup_fd);
	int32_t	error_log_fd = open(ERROR_LOG, O_RDONLY);
	if (error_log_fd < 0)
	{
		perror("Error log opening failed");
		return (false);
	}
	ft_bzero(error_buffer, 2048);
	read(error_log_fd, error_buffer, 2048 - 1);
	errno = 0;
	*error_message = ft_strdup(error_buffer);
	ret = true;
	if (*error_message == NULL && errno)
		ret = false;
	close(error_log_fd);
	unlink("error_log");
	return (ret);
}

