/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:17 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/16 09:54:36 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	line = NULL;
	if (gnl_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = gnl_strlen(buf[fd]);
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (old_len == gnl_strlen(buf[fd]))
			line = buf[fd];
	}
	if (!buf[fd] || !buf[fd][0])
		return (NULL);
	if (!line)
		line = gnl_substr(buf[fd], 0, gnl_strchr_i(buf[fd], '\n') + 1);
	buf[fd] = gnl_shrink_buffer(buf[fd], line);
	if (line && line[0])
		return (line);
	free(line);
	return (get_next_line(fd));
}

char	*gnl_shrink_buffer(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	line_len = gnl_strlen(line);
	newbuf = gnl_substr(buf, line_len, gnl_strlen(buf) - line_len);
	free(buf);
	if (!newbuf)
		return (NULL);
	if (newbuf[0] == '\0')
	{
		free(newbuf);
		return (NULL);
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
	char	*aux;
	int		nbytes;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (0);
	nbytes = read(fd, aux, BUFFER_SIZE);
	aux[nbytes] = '\0';
	if (!buf || !buf[0])
		return (aux);
	if (!aux || !aux[0])
	{
		free(aux);
		return (buf);
	}
	newlen = gnl_strlen(buf) + gnl_strlen(aux);
	newbuf = malloc(newlen + 1);
	ft_strlcpy(newbuf, buf, newlen + 1);
	gnl_strlcat(newbuf, aux, newlen + 1);
	free(buf);
	free(aux);
	return (newbuf);
}
