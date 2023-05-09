/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/09 12:27:18 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int	home_dir(t_env *aux)
{
	t_env	*env_lst;

	env_lst = fetch_node(aux, "HOME");
	if (!env_lst)
		write_error("cd: HOME not set\n", 1);
	else if (env_lst)
	{
		if (chdir(env_lst->value) != 0)
			error_m("cd", env_lst->value, "No such file or directory\n", 1);
		else
			return (0);
	}
	return (-1);
}

int	til_dir(t_env *aux)
{
	t_env	*env_lst;

	env_lst = fetch_node(aux, "HOME");
	if (!env_lst)
	{
		if (chdir(getenv("HOME")) != 0)
			error_m("cd", env_lst->value, "No such file or directory\n", 1);
		else
			return (0);
	}
	else if (env_lst)
	{
		if (chdir(env_lst->value) != 0)
			error_m("cd", env_lst->value, "No such file or directory\n", 1);
		else
			return (0);
	}
	return (-1);
}

int	go_home(char **param, t_env *env_lst)
{
	t_env	*aux;
	int		flag;
	char	oldpwd[1024];

	aux = env_lst;
	flag = -1;
	getcwd(oldpwd, sizeof(oldpwd));
	if (!param[1])
		flag = home_dir(aux);
	else if (ft_strcmp(param[1], "~") == 0)
		flag = til_dir(aux);
	if (flag == 0)
		update_var(aux, oldpwd);
	return (flag);
}

void	go_oldpwd(t_env *aux)
{
	t_env	*env_lst;

	env_lst = fetch_node(aux, "OLDPWD");
	if (!env_lst)
		write_error("cd: OLDPWD not set\n", 1);
	else if (env_lst)
	{
		if (chdir(env_lst->value) != 0)
			error_m("cd", env_lst->value, "No such file or directory\n", 1);
		else
			ft_printf("%s\n", env_lst->value);
	}
}

void	command_cd(char **param, t_env *env_lst)
{
	char	oldpwd[1024];
	t_env	*aux;
	int		i;

	g_exit_s = 0;
	aux = env_lst;
	getcwd(oldpwd, sizeof(oldpwd));
	i = 0;
	while (param[i])
		i++;
	if (i >= 3)
	{
		write_error("cd: too many arguments\n", 1);
		return ;
	}
	if (go_home(param, aux) == 0 || g_exit_s != 0)
		return ;
	if (ft_strcmp(param[1], "-") == 0)
		go_oldpwd(env_lst);
	else if (chdir(param[1]) != 0)
		error_m("cd", param[1], "No such file or directory\n", 1);
	update_var(aux, oldpwd);
}
