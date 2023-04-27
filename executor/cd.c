/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/20 18:37:13 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	update_var(t_env *env_lst, char *oldpwd)
{
	t_env	*aux;
	char	pwd[1024];

	aux = env_lst;
	env_lst = fetch_node(aux, "PWD");
	if (env_lst)
		env_lst->value = getcwd(pwd, sizeof(pwd));
	env_lst = fetch_node(aux, "OLDPWD");
	if (env_lst)
		env_lst->value = oldpwd;
	update_all(aux, *env());
}

void	write_error(char *str, int status)
{
	ft_putendl_fd(str, 2);
	g_exit_s = status;
}

void	no_file_message(char *command, char *param, int s)
{
	ft_putendl_fd(command, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(param, 2);
	ft_putendl_fd(": No such file or directory\n", 2);
	g_exit_s = s;
}

void	go_home(char **param, t_env *env_lst)
{
	t_env	*aux;

	aux = env_lst;
	if (!param[1])
	{
		env_lst = fetch_node(aux, "HOME");
		if (!env_lst)
			write_error("cd: HOME not set\n", 1);
		else if (env_lst)
			if (chdir(env_lst->value) != 0)
				no_file_message("cd", env_lst->value, 1);
	}
	else if (ft_strcmp(param[1], "~") == 0)
	{
		env_lst = fetch_node(aux, "HOME");
		if (!env_lst)
		{
			if (chdir(getenv("HOME")) != 0)
				no_file_message("cd", env_lst->value, 1);
		}
		else if (env_lst)
			if (chdir(env_lst->value) != 0)
				no_file_message("cd", env_lst->value, 1);
	}
}

void	command_cd(char **param, t_env *env_lst)
{
	char	oldpwd[1024];
	t_env	*aux;

	g_exit_s = 0;
	aux = env_lst;
	getcwd(oldpwd, sizeof(oldpwd));
	go_home(param, env_lst);
	if (g_exit_s != 0)
		return ;
	if (ft_strcmp(param[1], "-") == 0)
	{
		env_lst = fetch_node(aux, "OLDPWD");
		if (!env_lst)
			write_error("cd: OLDPWD not set\n", 1);
		else if (env_lst)
		{
			if (chdir(env_lst->value) != 0)
				no_file_message("cd", env_lst->value, 1);
			else
				ft_printf("%s\n", env_lst->value);
		}
	}
	else if (chdir(param[1]) != 0)
		no_file_message("cd", env_lst->value, 1);
	update_var(aux, oldpwd);
}
