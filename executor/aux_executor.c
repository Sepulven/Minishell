/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:47:21 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/15 17:04:27 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

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

int check_flags_one(char **param, char *command)
{
	int		j;

	j = 0;
	if (!param[1])
		return (0);
	while (param[1][j])
	{
		if (param[1][j] == '-' && param[1][j + 1])
		{
			ft_putstr_fd(command, 2);
			ft_putendl_fd(": ", 2);
			ft_putchar_fd(param[1][j], 2);
			ft_putchar_fd(param[1][j + 1], 2);
			ft_putendl_fd(": invalid option\n", 2);
			g_exit_s = 2;
			return (-1); 
		}
		j++;
	}
	return (0);
}

int check_flags_two(char **param, char *command)
{
	int	j;

	j = 1;
	if (!param[1])
		return (0);
	printf("param 1 %s\n", param[1]);
	while (param[1][j])
	{
		if (param[1][j] == '-' && param[1][j + 1])
		{
			error_m(command, param[1], ": invalid option\n", 2);
			return (-1);
		}
		j++;
	}
	return (0);
}
