/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:53:49 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/02 13:31:52 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	get_com(t_command_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	error_function(t_command_list *lst, int **fd, int status)
{
	g_exit_s = status;
	if (fd)
		free_pipes(fd, get_com(lst));
	free_lst(lst);
	free_envp(*env());
	exit(g_exit_s);
}

void	command(int **fd, t_command_list *lst, int i, int com)
{
	t_command_list	*node;

	node = get_lst(lst, i);
	if (i == 0)
		command_one(fd, node, i);
	else if (i == com - 1)
		command_final(fd, node, i);
	else
		command_middle(fd, node, i);
	check_builtin_first(node);
	check_builtin_second(node);
	execve(node->path, node->param, *env());
	perror(node->command);
	error_function(node, fd, 127);
}

int	*do_fork(t_command_list *lst, int **id, int i, int com)
{
	int	*pid;
	int	stat;

	pid = malloc(sizeof(int) * com);
	pid[i] = fork();
	if (pid[i] == -1)
	{
		ft_putendl_fd("Forked failed\n", 2);
		error_function(lst, 0, 127);
	}
	else if (pid[i] == 0)
		command(id, lst, i, com);
	else
	{
		waitpid(pid[i], &stat, 0);
		g_exit_s = WIFEXITED(stat);
	}
	return (pid);
}

void	execute_one(t_command_list *lst)
{
	int			p;
	struct stat	path_stat;

	p = fork();
	if (p == -1)
		error_function(lst, 0, 127);
	else if (p == 0)
	{
		if (lst->inf != 0)
			dup2(lst->inf, STDIN_FILENO);
		if (lst->outf != 0)
			dup2(lst->outf, STDOUT_FILENO);
		stat(lst->path, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putendl_fd("Is a directory\n", 2);
			error_function(lst, 0, 126);
		}
		execve(lst->path, lst->param, *env());
		perror(lst->command);
		error_function(lst, 0, 127);
	}
}

void	close_pipes(int **id, int com)
{
	int	i;

	i = 0;
	while (i != com - 1)
	{
		close(id[i][1]);
		i++;
	}
	i = 0;
	while (i != com - 1)
	{
		close(id[i][0]);
		i++;
	}
}

void	execute(t_command_list *lst, int com)
{
	int	i;
	int	f;
	int	**id;
	int	status;
	int	*pid;

	(void)f;
	i = 0;
	f = 3;
	id = 0;
	status = 0;
	if (com == 1)
	{
		if (check_builtin_one(lst) == -1)
			execute_one(lst);
	}
	else
	{
		id = create_pipes(com);
		while (i < com)
		{
			if (i != com - 1)
				pipe(id[i]);
			pid = do_fork(lst, id, i, com);
			// if (i != com - 1)
			// 	close(id[i][1]);
			i++;
		}
	}
	close_pipes(id, com);
	i = 0;
	//waitpid(-1, 0, 0);
	while (i != com - 1)
		waitpid(pid[i], &g_exit_s, 0);
	//waitpid(-1, &status, 0);
	free_pipes(id, com);
}
