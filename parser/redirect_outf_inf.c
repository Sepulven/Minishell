/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outf_inf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:10:27 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/16 18:38:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

extern int	g_exit_s;

int	redirect_outf(char *token)
{
	char	*file_name;
	char	*buff;
	int		fd;

	buff = ft_strdup(token);
	buff[ft_strlen(buff) - 1] = '\0';
	file_name = ft_strdup(&buff[2 + ft_iswhitespace(buff[2])]);
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		g_exit_s = 1;
		perror(&buff[2]);
	}
	free(buff);
	free(file_name);
	return (fd);
}

int	redirect_inf(char *token)
{
	char	*file_name;
	char	*buff;
	int		fd;

	buff = ft_strdup(token);
	buff[ft_strlen(buff) - 1] = '\0';
	file_name = ft_strdup(&buff[2 + ft_iswhitespace(buff[2])]);
	fd = open(file_name, O_RDONLY, 0444);
	if (fd == -1)
	{
		g_exit_s = 1;
		perror(&buff[2]);
	}
	free(buff);
	free(file_name);
	return (fd);
}
