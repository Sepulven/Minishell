/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/16 12:06:39 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

void	fetch_home(void)
{
	t_env	*env_lst;
	t_env	*aux;

	env_lst = get_env();
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
	free_env(env_lst);
}

void	command_pwd(char **param)
{
	char	pwd[1024];
	char	*path;

	g_exit_s = 0;
	path = getcwd(pwd, 500);
	if (param[1] && check_flags_one(param[1], "pwd") == -1)
		return ;
	if (path[0] != '\0')
		ft_printf("%s\n", pwd);
	else
		fetch_home();
}
