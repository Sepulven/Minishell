/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_outf_inf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:10:27 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 11:10:13 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

extern int	g_exit_s;

static char	*_filename(char *token)
{
	int		i;
	char	*filename;

	i = ft_isredirects(&token[0]);
	i += jump_white_spaces(&token[i]);
	filename = formatter(expander(ft_strdup(&token[i])));
	if (!filename)
		return (NULL);
	return (filename);
}

int	append(char *token)
{
	char	*file_name;
	int		fd;

	file_name = _filename(token);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		g_exit_s = 1;
		perror(file_name);
	}
	free(file_name);
	return (fd);
}

int	redirect_outf(char *token)
{
	char	*file_name;
	int		fd;

	file_name = _filename(token);
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		g_exit_s = 1;
		perror(file_name);
	}
	free(file_name);
	return (fd);
}

int	redirect_inf(char *token)
{
	char	*file_name;
	int		fd;

	file_name = _filename(token);
	fd = open(file_name, O_RDONLY, 0444);
	if (fd == -1)
	{
		g_exit_s = 1;
		perror(file_name);
	}
	free(file_name);
	return (fd);
}
