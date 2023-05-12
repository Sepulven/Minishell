/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/11 18:03:05 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int check_flags(char **param)
{
	int	i;
	int	j;

	i = 0;
	while (param[i])
	{
		j = 0;
		while (param[i][j])
		{
			if (param[i][j] == '-' && param[i][j + 1])
			{
				ft_putchar_fd(param[i][j], 2);
				ft_putchar_fd(param[i][j + 1], 2);
				ft_putendl_fd(": not a valid option\n", 2);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	command_pwd(t_env *env_lst, char **param)
{
	char	pwd[1024];
	t_env	*aux;
	char	*path;

	g_exit_s = 0;
	path = getcwd(pwd, 500);
	if (check_flags(param) == -1)
		error_function(0, 0, 2);
	if (path[0] != '\0')
		ft_printf("%s\n", pwd);
	else
	{
		aux = fetch_node(env_lst, "PWD");
		if (aux->name)
		{
			ft_putendl_fd(aux->value, 1);
			write(1, "\n", 1);
		}
		else
		{
			ft_putendl_fd(getenv("PWD"), 1);
			write(1, "\n", 1);
		}
	}
	free_env(env_lst);
}
