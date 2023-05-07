/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:08:43 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/07 13:41:42 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

int	ft_strcmp_getline(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] || b[i])
	{
		if (a[i] != b[i])
		{
			if (a[i] == '\n' && !b[i])
				return (1);
			return (-1);
		}
		i++;
	}
	return (1);
}

t_command_list	*here_doc(t_command_list *new, char **aux, int *i, int fd)
{
	char	*buf;
	char	*limiter;

	limiter = aux[*i + 1];
	if (fd != 0)
		close(fd);
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		if (ft_strcmp_getline(buf, limiter) == 1)
			break ;
		write(fd, buf, ft_strlen(buf));
	}
	free(buf);
	*i = *i + 2;
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	new->inf = fd;
	return (new);
}
