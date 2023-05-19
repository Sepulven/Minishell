/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:27:43 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/19 20:02:13 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int	check_cd(char **param)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (param[1] && check_flags_one(param[1], "cd") == -1)
		return (-1);
	if (i >= 3)
	{
		write_error("cd: too many arguments\n", 1);
		return (-1);
	}
	return (0);
}

int	check_flags_one(char *param, char *command)
{
	int		j;

	j = 0;
	if (param[0] != '-')
		return (0);
	while (param[j])
	{
		if (param[j] == '-' && param[j + 1])
		{
			ft_putstr_fd(command, 2);
			ft_putendl_fd(": ", 2);
			ft_putchar_fd(param[j], 2);
			ft_putchar_fd(param[j + 1], 2);
			ft_putendl_fd(": invalid option\n", 2);
			g_exit_s = 2;
			return (-1);
		}
		j++;
	}
	return (0);
}

int	check_flags_two(char **param, char *command)
{
	int	j;

	j = 0;
	if (!param[1])
		return (0);
	if (param[1][0] != '-')
		return (0);
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

void	is_dir(t_com_list *lst, int **fd)
{
	struct stat	path_stat;

	stat(lst->path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		if (!lst->command[0])
			error_function(lst, fd, 126, 1);
		if (ft_strncmp(lst->command, "./", 2) == 0)
		{
			error_m(0, lst->command, "Is a directory\n", 126);
			error_function(lst, fd, 126, 1);
		}
		else
		{
			error_m(0, lst->command, "Command not found\n", 127);
			error_function(lst, fd, 127, 1);
		}
	}
}
