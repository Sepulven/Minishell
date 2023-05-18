/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 17:33:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_delimitador(char *token)
{
	int		i;
	char	*aux;

	i = 0;
	i += jump_white_spaces(&token[i]);
	i += ft_isredirects(&token[i]);
	i += jump_white_spaces(&token[i]);
	aux = token;
	return (&aux[i]);
}

void	close_heredoc(int fd, char *delimitador, char *line, int i)
{
	(void)fd;
	if (!line)
		ft_printf(ERR_CTRL_D, i, delimitador);
	else if (line)
		free(line);
	exit(EXIT_SUCCESS);
}

static void	heredoc_process(int fd, char *token)
{
	char	*line;
	int		i;
	int		expand_flag;
	char	*delimitador;

	i = 0;
	expand_flag = 1;
	(void)expand_flag;
	delimitador = get_delimitador(token);
	// if (ft_strrchr(delimitador, '"') || ft_strrchr(delimitador, '\''))
	// 	expand_flag = 0;
	// delimitador = formatter(delimitador);
	while (1)
	{
		ft_printf("heredoc:>");
		line = get_next_line(0);
		i++;
		if (line == NULL || !ft_strncmp(line, delimitador, \
		ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n')))
			close_heredoc(fd, delimitador, line, i);
		// if (expand_flag)
		// 	line = expander(line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	heredoc(char *token)
{
	int		pid;
	char	*pathname;
	int		fd;

	(void)pid;
	pathname = take_avaible_filename();
	fd = open(pathname, O_WRONLY | O_CREAT, 0644);
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Forked failed\n", 2);
	else if (pid == 0)
	{
		signal(SIGINT, NULL);
		signal(SIGQUIT, SIG_IGN);
		heredoc_process(fd, token);
	}
	wait(NULL);
	close(fd);
	fd = open(pathname, O_RDONLY, 0444);
	if (pathname)
		free(pathname);
	return (fd);
}
