/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/27 17:39:33 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	check_flag_n(char *str)
{
	int	f;
	int	flag;

	f = 2;
	flag = 1;
	if (ft_strcmp(str, "-n") == 0)
		return (1);
	else if (ft_strlen(str) > 2 && ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[f])
		{
			if (str[f] != 'n')
				flag = 0;
			f++;
		}
		if (flag == 1)
			return (1);
	}
	return (0);
}

void	command_echo(char **param)
{
	int	n;
	int	i;
	int	f;

	n = 0;
	i = 1;
	while (param[i])
	{
		f = 0;
		while (param[i] && check_flag_n(param[i]) == 1)
		{
			n = 1;
			i++;
		}
		while (param[i][f])
		{
			if (param[i][f] == '$' && param[i][f + 1] == '?')
			{
				ft_printf("%i", g_exit_s);
				f++;
			}
			else
				ft_printf("%c", param[i][f]);
			f++;
		}
		if (param[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n == 0)
		write(1, "\n", 1);
}
