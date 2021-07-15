/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:14:39 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/14 22:53:31 by aperez-b         ###   ########.fr       */
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
		if (!line)
			return (0);
		ft_printf("Line %d: \"%s\"\n", i, line);
		free(line);
		i++;
	}
}
