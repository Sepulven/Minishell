/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 14:42:53 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_delimidator(char *token)
{
	char	*delimitador;

	return (delimitador);
}

// #define TESTE :

// int	heredoc(char *token)
// {
// 	char	*delimitador;
// 	char	*line;
// 	int		pipefd[2];

// 	delimitador = get_delimitador(token);
// 	pipe(pipefd);
// 	while (ft_strncmp())
// 	{
// 		line = get_next_line(0);
// 		write(pipefd[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(pideft[1]);
// }
