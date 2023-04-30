/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/30 18:21:42 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	command_one(int **fd, t_command_list *node, int i)
{
	close(fd[i][0]);
	if (node->inf == -1)
		exit(0);
	if (node->inf != 0)
	{
		dup2(node->inf, STDIN_FILENO);
		close(node->inf);
	}
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
	else
		dup2(fd[i][1], STDOUT_FILENO);
}

void	command_final(int **fd, t_command_list *node, int i)
{
	close(fd[i - 1][1]);
	if (node->inf == -1)
		exit(0);
	else if (node->inf != 0)
		dup2(node->inf, STDIN_FILENO);
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
	}
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
}

void	command_middle(int **fd, t_command_list *node, int i)
{
	close(fd[i][0]);
	close(fd[i - 1][1]);
	if (node->inf == -1)
		exit(0);
	else if (node->inf != 0)
	{
		dup2(node->inf, STDIN_FILENO);
		close(node->inf);
	}
	else
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (node->outf != 0)
	{
		dup2(node->outf, STDOUT_FILENO);
		close(node->outf);
	}
	else
		dup2(fd[i][1], STDOUT_FILENO);
}
