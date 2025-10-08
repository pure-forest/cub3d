/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_error_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:02:51 by juaho             #+#    #+#             */
/*   Updated: 2025/07/09 16:41:52 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/errors.h"
#include "../../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd = open("log.txt", O_CREAT | O_WRONLY, 00644);
	if (fd < 0)
	{
		perror("open");
		exit (1);
	}
	int fd2 = open("log.txt", O_RDONLY);
	if (fd2 < 0)
	{
		perror("open");
		close(fd);
		exit (1);
	}
	if (dup2(fd, STDERR_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	print_error("a", "b");
	print_error("c", 0);

	char *expected =
		"Error\n" \
		"a: b\n" \
		"Error\n" \
		"c\n";

	static char buf[128];
	read(fd2, buf, 127);
	close(fd2);
	close(STDERR_FILENO);
	unlink("log.txt");

	printf("\033[01;33mOutput:\033[0m\n%s\n", buf);
	printf("\033[01;93mExpected:\033[0m\n%s\n", expected);

	if (ft_strncmp(buf, expected, 128))
	{
		printf("❌ \033[01;91mMISMATCH\033[0m\n");
		return (1);
	}
	else
	{
		printf("✅ \033[01;92mMATCH\033[0m\n");
		return (0);
	}
}
