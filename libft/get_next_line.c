/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:41:24 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/28 16:02:50 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlength(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	return (count + (str[count] == '\n'));
}

static char	*ft_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(ft_strlength(s1) + ft_strlength(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = (char)s1[j++];
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
		str[i++] = (char)s2[j++];
	if (s2[j] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	if (s1)
		free((void *)s1);
	return (str);
}

static char	*orgbuf(char *buf, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	i += (buf[i] == '\n');
	j = 0;
	while (i < BUFFER_SIZE)
		buf[j++] = buf[i++];
	buf[j++] = 0;
	return (line);
}

static int	checkeol(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
		if (buf[i++] == '\n')
			return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[FOPEN_MAX][BUFFER_SIZE + 1];
	size_t			i;

	i = 0;
	line = NULL;
	if (read(fd, 0, 0) || fd >= FOPEN_MAX || fd < 0)
	{
		while (fd >= 0 && fd <= FOPEN_MAX && i < BUFFER_SIZE)
			buf[fd][i++] = 0;
		return (NULL);
	}
	if (buf[fd][0] == 0)
		buf[fd][read(fd, buf[fd], BUFFER_SIZE)] = 0;
	while (buf[fd][0])
	{
		line = ft_join(line, buf[fd]);
		if (!line)
			return (NULL);
		if (checkeol(buf[fd]))
			return (orgbuf(buf[fd], line));
		buf[fd][read(fd, buf[fd], BUFFER_SIZE)] = 0;
	}
	return (line);
}
