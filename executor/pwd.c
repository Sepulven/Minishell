/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/20 17:50:31 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	command_pwd(t_env *env_lst)
{
	char	*pwd;
	t_env	*aux;

	pwd = NULL;
	g_exit_s = 0;
	getcwd(pwd, 500);
	if (pwd)
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
	free(pwd);
}
