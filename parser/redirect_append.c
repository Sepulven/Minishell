/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:52 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/09 14:58:03 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

int	append(char *token)
{
	char	*file_name;
	char	*buff;
	int		fd;

	buff = ft_strdup(token);
	buff[ft_strlen(buff) - 1] = '\0';
	file_name = ft_strdup(&buff[3 + ft_iswhitespace(buff[3])]);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(&buff[2]);
		return (-1);
	}
	free(buff);
	return (fd);
}
