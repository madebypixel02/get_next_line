/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:14:39 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/15 12:31:27 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>
#include "../../ft_printf/lib/ft_printf.h"

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 1;
	//fd = open("tests/J. K. Rowling - Harry Potter 1 - Sorcerer's Stone.txt", O_RDONLY);
	fd = open("tests/test.txt", O_RDONLY);
	//fd = open("tests/basic_oneline.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		ft_printf("Line %d: %s", i, line);
		if (!line)
		{
			free(line);
			return (0);
		}
		system("leaks a.out");
		free(line);
		i++;
	}
}
