/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/16 11:22:56 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

extern int	g_exit_s;

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

void	clear_exit(t_com_list *lst)
{
	free_lst(lst);
	free_envp(*env());
	exit(g_exit_s);
}

void	command_exit(t_com_list *lst)
{
	ft_printf("exit\n");
	g_exit_s = 0;
	if (!lst->param[1])
		clear_exit(lst);
	else if (check_exit(lst->param[1]) == -1)
	{
		error_m("exit", lst->param[1], "numeric argument required\n", 2);
		clear_exit(lst);
	}
	else if (lst->param[2])
	{
		ft_putendl_fd("exit: too many arguments\n", 2);
		g_exit_s = 1;
	}
	else
	{
		g_exit_s = check_exit(lst->param[1]);
		clear_exit(lst);
	}
}
