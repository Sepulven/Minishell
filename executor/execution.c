/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:53:49 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/19 17:16:08 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int	do_fork(t_com_list *lst, int **id, int i, int com)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Forked failed\n", 2);
		error_function(lst, 0, 127, -1);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, handler_quit);
		command(id, lst, i, com);
	}
	signal(SIGQUIT, handler);
	return (pid);
}

void	dups_dir(t_com_list *lst)
{
	if (lst->inf == -1)
		error_function(lst, 0, 1, -1);
	if (lst->inf != 0)
	{
		dup2(lst->inf, STDIN_FILENO);
		close(lst->inf);
	}
	if (lst->outf == -1)
		error_function(lst, 0, 1, -1);
	if (lst->outf != 0)
	{
		dup2(lst->outf, STDOUT_FILENO);
		close(lst->outf);
	}
	if (lst->path && access(lst->path, R_OK) == 0)
		is_dir(lst, 0);
}

void	execute_one(t_com_list *lst, int com)
{
	int			pid;
	int			status;

	pid = fork();
	if (pid == -1)
		error_function(lst, 0, 127, -1);
	else if (pid == 0)
	{
		dups_dir(lst);
		builtins(lst, 0, lst, com);
		execve(lst->path, lst->param, *env());
		perror(lst->command);
		error_function(lst, 0, 127, -1);
	}
	else
	{
		signal(SIGQUIT, handler_quit);
		wait(&status);
		if (WIFEXITED(status))
			g_exit_s = WEXITSTATUS(status);
		signal(SIGQUIT, handler);
	}
}

int	**do_loop(t_com_list *lst, int com, int *i, int *status)
{
	int	**id;
	int	aux;

	id = create_pipes(com);
	while (*i < com)
	{
		if (*i != com - 1)
			pipe(id[*i]);
		aux = do_fork(lst, id, *i, com);
		if (*i != com - 1)
			close(id[*i][1]);
		*i += 1;
	}
	close_pipes(id, com);
	waitpid(aux, status, 0);
	signal(SIGQUIT, handler_quit);
	while (*i >= 0)
	{
		wait(NULL);
		*i -= 1;
	}
	signal(SIGQUIT, handler);
	free_pipes(id, com);
	return (id);
}

void	execute(t_com_list *lst, int com)
{
	int	i;
	int	**id;
	int	status;

	i = 0;
	id = 0;
	(void)id;
	g_exit_s = 0;
	status = 0;
	if (com == 1)
	{
		if (!lst->command)
			return ;
		if (check_builtin_one(lst) == -1)
			execute_one(lst, com);
	}
	else
	{
		id = do_loop(lst, com, &i, &status);
		if (WIFEXITED(status))
			g_exit_s = WEXITSTATUS(status);
	}
	delete_heredoc_files();
	free_lst(lst);
}
