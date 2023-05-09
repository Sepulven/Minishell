/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:47:21 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/09 12:24:12 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"
// #include "../important.h"

extern int	g_exit_s;

void	write_error(char *str, int status)
{
	ft_putendl_fd(str, 2);
	g_exit_s = status;
}

void	error_m(char *command, char *param, char *str, int s)
{
	if (command)
	{
		ft_putendl_fd(command, 2);
		ft_putendl_fd(": ", 2);
	}
	ft_putendl_fd(param, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(str, 2);
	g_exit_s = s;
}

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
