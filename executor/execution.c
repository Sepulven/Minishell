/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:53:49 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/09 13:15:24 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int	do_fork(t_command_list *lst, int **id, int i, int com)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Forked failed\n", 2);
		error_function(lst, 0, 127);
	}
	else if (pid == 0)
		command(id, lst, i, com);
	return (pid);
}

void	dups_dir(t_command_list *lst)
{
	struct stat	path_stat;

	if (lst->inf != 0)
		dup2(lst->inf, STDIN_FILENO);
	if (lst->outf != 0)
		dup2(lst->outf, STDOUT_FILENO);
	stat(lst->path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		if (ft_strncmp(lst->command, "./", 2) == 0)
		{
			error_m(0, lst->command, "Is a directory\n", 126);
			error_function(lst, 0, 126);
		}
		else
		{
			error_m(0, lst->command, "Command not found\n", 127);
			error_function(lst, 0, 127);
		}
	}
}

void	execute_one(t_command_list *lst)
{
	int			pid;
	int			status;

	pid = fork();
	if (pid == -1)
		error_function(lst, 0, 127);
	else if (pid == 0)
	{
		dups_dir(lst);
		check_builtin(lst);
		execve(lst->path, lst->param, *env());
		perror(lst->command);
		error_function(lst, 0, 127);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_exit_s = WEXITSTATUS(status);
	}
}

int	**do_loop(t_command_list *lst, int com, int *i, int *status)
{
	int	pid;
	int	**id;

	id = create_pipes(com);
	pid = 0;
	while (*i < com)
	{
		if (*i != com - 1)
			pipe(id[*i]);
		pid = do_fork(lst, id, *i, com);
		if (*i != com - 1)
			close(id[*i][1]);
		*i += 1;
	}
	close_pipes(id, com);
	waitpid(pid, status, 0);
	while (*i >= 0)
	{
		wait(NULL);
		*i -= 1;
	}
	return (id);
}

void	execute(t_command_list *lst, int com)
{
	int	i;
	int	**id;
	int	status;

	i = 0;
	id = 0;
	g_exit_s = 0;
	status = 0;
	if (com == 1)
	{
		if (check_builtin_one(lst) == -1)
			execute_one(lst);
	}
	else
	{
		id = do_loop(lst, com, &i, &status);
		if (WIFEXITED(status))
			g_exit_s = WEXITSTATUS(status);
	}
	free_pipes(id, com);
}
