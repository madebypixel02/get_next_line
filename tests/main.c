/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:14:39 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/17 20:34:07 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd_1;
	int		fd_2;
	int		i;
	char	*line[4096];

	i = 1;
	fd_1 = open("tests/J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt", O_RDONLY);
	//fd_1 = open("tests/test.txt", O_RDONLY);
	//fd_2 = open("tests/test2.txt", O_RDONLY);
	//fd = open("tests/empty.txt", O_RDONLY);
	//fd_1 = open("tests/41_no_nl.txt", O_RDONLY);
	//fd = open("tests/big_line_no_nl.txt", O_RDONLY);
	//fd_2 = open("tests/basic_oneline.txt", O_RDONLY);
	fd_2 = open("tests/the-king-james-bible.txt", O_RDONLY);
	while (1)
	{
		line[fd_1] = get_next_line(fd_1);
		line[fd_2] = get_next_line(fd_2);
		printf("Line %d for fd %d: %s\n", i, fd_1, line[fd_1]);
		printf("Line %d for fd %d: %s\n", i, fd_2, line[fd_2]);
		if (!line[fd_1] && line[fd_2])
		{
			free(line[fd_2]);
			//system("leaks a.out");
			return (0);
		}
		if (line[fd_1] && !line[fd_2])
		{
			free(line[fd_1]);
			//system("leaks a.out");
			return (0);
		}
		free(line[fd_1]);
		free(line[fd_2]);
		i++;
	}
}
