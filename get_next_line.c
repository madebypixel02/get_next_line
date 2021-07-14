/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:17 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/14 14:54:17 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	int			nbytes;
	char		*line;

	nbytes = -1;
	if (!buf[fd])
	{
		//ft_printf("Buffer empty! Reading again...\n");
		buf[fd] = malloc(BUFFER_SIZE + 1);
		nbytes = read(fd, buf[fd], BUFFER_SIZE);
		if (!nbytes)
			return (NULL);
		buf[fd][nbytes] = '\0';
	}
	else
	{
		if (nbytes)
			buf[fd] = gnl_shrink_buffer(buf[fd], gnl_strchr_i(buf[fd], '\n') + 1);
		else
			buf[fd] = gnl_shrink_buffer(buf[fd], gnl_strlen(buf[fd]));
		
		//ft_printf("Increasing buffer contents with new read...\n");
		//buf[fd] = gnl_expand_buffer(buf[fd], fd);
	}
	line = gnl_get_line(buf[fd]);
	if (line)
	{
		buf[fd] = gnl_shrink_buffer(buf[fd], gnl_strchr_i(buf[fd], '\n') + 1);
		printf("BUF: \"%s\"\n", buf[fd]);
		if (buf[fd])
			return (line);
	}
	free(line);
	return (get_next_line(fd));
}

char	*gnl_get_line(char *buf)
{
	int	newline_i;

	if (!buf)
		return (NULL);
	newline_i = gnl_strchr_i(buf, '\n');
	if (newline_i != -1)
		return(gnl_substr(buf, 0, newline_i + 1));
	return (buf);
}

char	*gnl_shrink_buffer(char *buf, int i)
{
	char	*newbuf;

	newbuf = gnl_substr(buf, i, gnl_strlen(buf) - i);
	if (!newbuf)
		return (NULL);
	if (gnl_strlen(buf) == gnl_strlen(newbuf))
	{
		free(newbuf);
		newbuf = NULL;
	}
	else
		free(buf);
	return (newbuf);
}

char	*gnl_expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	char	*aux;
	int		nbytes;

	aux =  malloc(BUFFER_SIZE + 1);
	nbytes = read(fd, aux, BUFFER_SIZE);
	aux[nbytes] = '\0';
	newlen = gnl_strlen(buf) + gnl_strlen(aux);
	newbuf = malloc(newlen + 1);
	gnl_strlcpy(newbuf, buf, gnl_strlen(buf) + 1);
	gnl_strlcat(newbuf, aux, newlen + 1);
	free(buf);
	buf = NULL;
	free(aux);
	aux = NULL;
	return (newbuf);
}
