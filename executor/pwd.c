/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/15 18:03:03 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

void	command_pwd(char **param)
{
	char	pwd[1024];
	t_env	*aux;
	char	*path;
	t_env	*env_lst;

	g_exit_s = 0;
	(void)env_lst;
	path = getcwd(pwd, 500);
	if (param[1] && check_flags_one(param[1], "pwd") == -1)
		return ;
	if (path[0] != '\0')
		ft_printf("%s\n", pwd);
	else
	{
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
}
