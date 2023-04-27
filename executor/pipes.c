/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:35:54 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/21 17:11:24 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	do_dups(int fin, int fout, int fd_close)
{
	if (fin != 0)
		dup2(fin, STDIN_FILENO);
	if (fout != 0)
		dup2(fout, STDOUT_FILENO);
	if (fd_close)
		close(fd_close);
}

t_command_list	*get_lst(t_command_list *lst, int i)
{
	int				f;
	t_command_list	*node;

	f = 0;
	node = lst;
	while (f < i)
	{
		node = node->next;
		f++;
	}
	return (node);
}

int	**create_pipes(int com)
{
	int	i;
	int	f;
	int	**id;

	i = 0;
	f = 3;
	id = 0;
	id = malloc(sizeof(int *) * (com - 1));
	if (!id)
		exit(0);
	while (i < com - 1)
	{
		id[i] = malloc(sizeof(int) * 2);
		id[i][0] = f;
		id[i][1] = f + 1;
		f = f + 2;
		i++;
	}
	return (id);
}

void	free_pipes(int **id, int com)
{
	int	i;

	i = 0;
	while (i < com - 1)
	{
		free(id[i]);
		i++;
	}
	free(id);
}
