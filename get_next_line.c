/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:17 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/15 12:30:10 by aperez-b         ###   ########.fr       */
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
		//ft_printf("No newline found, attempting new read...\n");
		old_len = gnl_strlen(buf[fd]);
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (old_len == gnl_strlen(buf[fd]))
		{
			//ft_printf("Nothing new read!!\n");
			line = buf[fd];
		}
	}
	//ft_printf("BUF2: %s\n", buf[fd]);
	if (!buf[fd] || !buf[fd][0])
		return (NULL);
	if (!line)
		line = gnl_substr(buf[fd], 0, gnl_strchr_i(buf[fd], '\n') + 1);
	buf[fd] = gnl_shrink_buffer(buf[fd], line);
	//ft_printf("LINE: %s\n", line);
	if (line && line[0])
		return (line);
	return (get_next_line(fd));
}

char	*gnl_shrink_buffer(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	line_len = gnl_strlen(line);
	newbuf = gnl_substr(buf, line_len, gnl_strlen(buf) - line_len);
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
	char	*aux;
	int		nbytes;

	aux = malloc(BUFFER_SIZE + 1);
	if (!aux)
		return (0);
	nbytes = read(fd, aux, BUFFER_SIZE);
	aux[nbytes] = '\0';
	//ft_printf("AUX: %s\n", aux);
	//ft_printf("BUF: %s\n", buf);
	if (!buf || !buf[0])
	{
		//ft_printf("Buffer empty, filling with: %s\n", aux);
		newbuf = aux;
		return (newbuf);
	}
	if (!aux || !aux[0])
	{
		//ft_printf("Nothing read, returning buffer: %s\n", buf);
		newbuf = buf;
		return (newbuf);
	}
	newlen = gnl_strlen(buf) + gnl_strlen(aux);
	//ft_printf("Merging strings, total length is %d\n", newlen);
	newbuf = malloc(newlen + 1);
	ft_strlcpy(newbuf, buf, newlen + 1);
	gnl_strlcat(newbuf, aux, newlen + 1);
	//ft_printf("NEWBUF: %s\n", newbuf);
	free(buf);
	free(aux);
	return (newbuf);
}
