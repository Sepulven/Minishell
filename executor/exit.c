/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/28 10:31:40 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_digits(const char *nptr, int count)
{
	while (nptr[count])
	{
		if (ft_isdigit(nptr[count]) == 0)
			return (-1);
		count++;
	}
	return (1);
}

int	check_exit(const char *nptr)
{
	int	count;
	int	number;
	int	aux;
	int	signal;

	number = 0;
	count = 0;
	signal = 1;
	while ((nptr[count] == 32) || ((nptr[count] >= 9) && (nptr[count] <= 13)))
		count++;
	if ((nptr[count] == '+') || (nptr[count] == '-'))
	{
		if ((nptr[count] == '-'))
			signal = -1;
		count++;
	}
	aux = count;
	if (check_digits(nptr, count) == -1)
		return (-1);
	while (ft_isdigit(nptr[aux]))
	{
		number = (number * 10) + nptr[aux] - 48;
		aux++;
	}
	return (number * signal);
}

void	clear_exit(t_command_list *lst)
{
	free_lst(lst);
	free_envp(*env());
	exit(g_exit_s);
}

void	command_exit(t_command_list *lst)
{
	ft_printf("exit\n");
	g_exit_s = 0;
	if (!lst->param[1])
		clear_exit(lst);
	else if (check_exit(lst->param[1]) == -1)
	{
		no_file_message("exit", lst->param[1], 2);
		clear_exit(lst);
	}
	else if (lst->param[2])
	{
		write(2, "exit: too many arguments\n", 25);
		g_exit_s = 1;
	}
	else
	{
		g_exit_s = check_exit(lst->param[1]);
		clear_exit(lst);
	}
}
