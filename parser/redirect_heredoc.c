/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 09:43:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_delimitador(char *token)
{
	char	*delimitador;

	delimitador = ft_strdup(&token[3 + ft_iswhitespace(token[3])]);
	delimitador[ft_strlen(delimitador) - 1] = '\0';
	return (delimitador);
}

static void	heredoc_process(int fd, char *delimitador)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		ft_printf("heredoc:>");
		line = get_next_line(0);
		i++;
		if (line == NULL || !ft_strncmp(line, delimitador, \
		ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n')))
		{
			if (!line)
				ft_printf("\nhere-document at line %d delimited \
				by end-of-file (wanted '%s')\n", i, delimitador);
			else if (line)
				free(line);
			free(delimitador);
			close(fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	heredoc(char *token)
{
	int		pid;
	char	*pathname;
	char	*delimitador;

	pathname = take_avaible_filename();
	delimitador = get_delimitador(token);
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("Forked failed\n", 2);
	else if (pid == 0)
	{
		signal(SIGINT, NULL);
		signal(SIGQUIT, SIG_IGN);
		heredoc_process(open(pathname, O_WRONLY | O_CREAT, 0644), delimitador);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	return (open(pathname, O_RDONLY, 0444));
}
