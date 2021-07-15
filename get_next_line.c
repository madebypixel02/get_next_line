/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:17 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/14 23:08:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;

	if (gnl_strchr_i(buf[fd], '\n') == -1) 
	{
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (!buf[fd])
			return (NULL);
	}
	line = gnl_get_line(buf[fd], gnl_strchr_i(buf[fd], '\n'));
	buf[fd] = gnl_shrink_buffer(buf[fd], gnl_strchr_i(buf[fd], '\n') + 1);
	if (line && line[0] != '\0')
		return (line);
	return (NULL);
	return (get_next_line(fd));
}

char	*gnl_shrink_buffer(char *buf, int i)
{
	char	*newbuf;

	newbuf = gnl_substr(buf, i, gnl_strlen(buf) - i);
	if (!newbuf)
		return (NULL);
	if (newbuf[0] == '\0')
	{
		free(newbuf);
		newbuf = NULL;
	}
	return (newbuf);
}

char	*gnl_get_line(char *buf, int i)
{
	char	*line;

	line = gnl_substr(buf, 0, i + 1);
	return (line);
}

char	*gnl_expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	int		nbytes;
	char	*aux;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (0);
	nbytes = read(fd, aux, BUFFER_SIZE);
	aux[nbytes] = '\0';
	newlen = gnl_strlen(buf) + gnl_strlen(aux);
	if (buf)
	{
		newbuf = malloc(newlen + 1);
		gnl_strlcpy(newbuf, buf, gnl_strlen(buf) + 1);
		gnl_strlcat(newbuf, aux, newlen + 1);
		free(buf);
	}
	else
		newbuf = aux;

	free(aux);
	return (newbuf);
}
