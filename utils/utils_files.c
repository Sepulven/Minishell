/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:20:35 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 20:00:42 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

char	*get_pathname(int index)
{
	char	*s_index;
	char	*pathname;

	s_index = ft_itoa(index);
	if (!s_index)
		return (NULL);
	pathname = ft_strjoin("./.heredoc_files/", s_index);
	free(s_index);
	return (pathname);
}

char	*take_avaible_filename(void)
{
	char	*pathname;
	int		i;

	i = 0;
	pathname = NULL;
	while (!pathname)
	{
		pathname = get_pathname(i++);
		if (access(pathname, R_OK) == -1)
			return (pathname);
		free(pathname);
		pathname = NULL;
	}
	return (NULL);
}

char	*take_current_pathname(void)
{
	char	*pathname1;
	char	*pathname2;
	int		i;

	i = 0;
	pathname1 = NULL;
	pathname2 = NULL;
	while (!pathname1 || !pathname2)
	{
		pathname1 = get_pathname(i);
		if (access(pathname1, R_OK) == -1 && i == 0)
			return (pathname1);
		else if (access(pathname1, R_OK) == -1)
		{
			free(pathname1);
			return (pathname2);
		}
		if (pathname2)
			free(pathname2);
		pathname2 = pathname1;
		pathname1 = NULL;
		i++;
	}
	return (NULL);
}

void	delete_heredoc_files(void)
{
	char	*pathname;
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	pathname = NULL;
	while (flag)
	{
		pathname = get_pathname(i++);
		if (unlink(pathname) == -1)
			flag = 0;
		if (pathname)
			free(pathname);
	}
}

void	delete_current_heredoc(int inf)
{
	char	*pathname;

	close(inf);
	pathname = take_current_pathname();
	unlink(pathname);
	free(pathname);
}
