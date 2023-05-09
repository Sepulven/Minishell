/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/09 12:27:25 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

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

	n = 0;
	i = 0;
	while (param[++i] && check_flag_n(param[i]) == 1)
		n = 1;
	while (param[i])
	{
		ft_printf("%s", param[i]);
		if (param[++i])
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
