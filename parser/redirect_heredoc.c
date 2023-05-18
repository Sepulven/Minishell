/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:14:29 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 14:32:21 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int	g_exit_s;

char	*get_delimitador(char *token)
{
	int		i;

	i = 0;
	i += jump_white_spaces(&token[i]);
	i += ft_isredirects(&token[i]);
	i += jump_white_spaces(&token[i]);
	return (ft_strdup(&token[i]));
}

void	close_heredoc(int fd, char *delimitador, char *line, int i)
{
	if (!line)
		ft_printf(ERR_CTRL_D, i, delimitador);
	else if (line)
		free(line);
	free(delimitador);
	free_envp(*env());
	close(fd);
	g_exit_s = EXIT_SUCCESS;
	exit(g_exit_s);
}

static void	stop_execution(void)
{
	return ;
}

static void	heredoc_process(int fd, char *token)
{
	char	*line;
	int		i;
	int		expand_flag;
	char	*delimitador;

	i = 0;
	expand_flag = 1;
	delimitador = get_delimitador(token);
	if (ft_strrchr(delimitador, '"') || ft_strrchr(delimitador, '\''))
		expand_flag = 0;
	delimitador = formatter(delimitador);
	while (1)
	{
		ft_printf("heredoc:>");
		line = get_next_line(0);
		i++;
		if (line == NULL || !ft_strncmp(line, delimitador, \
		ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n')))
			close_heredoc(fd, delimitador, line, i);
		if (expand_flag)
			line = expander(line);
		if (write(fd, line, ft_strlen(line)) == -1)
			stop_execution();
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
	}
	wait(NULL);
	return (open(pathname, O_RDONLY, 0444));
}
