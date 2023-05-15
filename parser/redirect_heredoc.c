/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 17:08:41 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_delimitador(char *token)
{
	char	*delimitador;

	delimitador = ft_strdup(&token[3]);
	delimitador[ft_strlen(delimitador) - 1] = '\0';
	return (delimitador);
}

static void	heredoc_process(int fd, char	*delimitador)
{
	char	*line;

	line = ft_strdup("");
	while (ft_strncmp(line, delimitador, ft_strlen(delimitador)) != 0)
	{
		free(line);
		ft_printf("here_doc:>");
		line = get_next_line(0);
		write(fd, line, ft_strlen(line));
	}
	close(fd);
}

int	heredoc(char *token, int command_index)
{
	int		pid;
	char	*pathname;
	char	*delimitador;

	pathname = get_pathname(command_index);
	delimitador = get_delimitador(token);
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Forked failed\n", 2);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		heredoc_process(open(pathname, O_WRONLY | O_CREAT, 0644), delimitador);
	}
	wait(NULL);
	return (open(pathname, O_RDONLY, 0444));
}
