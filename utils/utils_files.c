/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:20:35 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 16:05:07 by asepulve         ###   ########.fr       */
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
		pathname = get_pathname(i);
		i++;
		if (unlink(pathname) == -1)
			flag = 0;
		if (pathname)
			free(pathname);
	}
}
