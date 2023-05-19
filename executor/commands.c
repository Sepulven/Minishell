/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/19 14:56:15 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	command(int **fd, t_com_list *lst, int i, int com)
{
	t_com_list		*node;

	node = get_lst(lst, i);
	if (i == 0)
		command_one(fd, node, i);
	else if (i == com - 1)
		command_final(fd, node, i);
	else
		command_middle(fd, node, i);
	if (node->path && access(node->path, R_OK) == 0)
		is_dir(node, fd);
	builtins(lst, fd, node, com);
	free_pipes(fd, com);
	execve(node->path, node->param, *env());
	perror(node->command);
	error_function(lst, fd, 127, -1);
}

void	command_one(int **fd, t_com_list *node, int i)
{
	close(fd[i][0]);
	if (node->inf == -1)
		error_function(node, fd, 1, 1);
	if (node->inf != 0)
	{
		dup2(node->inf, STDIN_FILENO);
		close(node->inf);
	}
	if (node->outf == -1)
		error_function(node, fd, 1, 1);
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
	else
		dup2(fd[i][1], STDOUT_FILENO);
}

void	command_final(int **fd, t_com_list *node, int i)
{
	close(fd[i - 1][1]);
	if (node->inf == -1)
		error_function(node, fd, 1, 1);
	else if (node->inf != 0)
		dup2(node->inf, STDIN_FILENO);
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
	}
	if (node->outf == -1)
		error_function(node, fd, 1, 1);
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
}

void	command_middle(int **fd, t_com_list *node, int i)
{
	close(fd[i][0]);
	close(fd[i - 1][1]);
	if (node->inf == -1)
		error_function(node, fd, 1, 1);
	else if (node->inf != 0)
	{
		dup2(node->inf, STDIN_FILENO);
		close(node->inf);
	}
	else
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (node->outf == -1)
		error_function(node, fd, 1, 1);
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
	else
		dup2(fd[i][1], STDOUT_FILENO);
}
