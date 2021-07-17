/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 10:59:42 by aperez-b          #+#    #+#             */
/*   Updated: 2021/07/17 19:08:04 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
int		gnl_strchr_i(const char *s, int c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
size_t	gnl_strlcat(char *dst, const char *src, size_t size);
char	*gnl_shrink_buffer(char *buf, char *line);
char	*gnl_expand_buffer(char *buf, int fd);
char	*gnl_newread(int fd);
#endif
