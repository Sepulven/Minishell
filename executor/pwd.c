/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/15 16:53:00 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

void	command_pwd(t_env *env_lst, char **param)
{
	char	pwd[1024];
	t_env	*aux;
	char	*path;

	g_exit_s = 0;
	path = getcwd(pwd, 500);
	if (check_flags_one(param, "pwd") == -1)
		return ;
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
}
