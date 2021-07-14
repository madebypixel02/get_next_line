/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/14 14:15:35 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include "../ft_printf/lib/ft_printf.h"

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
int		gnl_strchr_i(const char *s, int c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_get_line(char *buf);
size_t	gnl_strlcat(char *dst, const char *src, size_t size);
char	*gnl_shrink_buffer(char *buf, int i);
char    *gnl_expand_buffer(char *buf, int fd);
#endif
