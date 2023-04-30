/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/30 20:19:57 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_param(char *param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		if (param[i] == '-' && param[i + 1])
		{
			error_m("unset: ", param, ": invalid option\n", 2);
			return (-1);
		}
		else if (param[i] == '=' || ft_isalnum(param[i]) == 0)
		{
			error_m("unset: `", param, "': not a valid identifier\n", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	unset_var(char *param, t_env *env_lst)
{
	t_env	*aux;
	t_env	*first_node;
	int		flag;

	first_node = env_lst;
	flag = 0;
	if (check_param(param) == -1)
	{
		g_exit_s = 1;
		return ;
	}
	while (env_lst && env_lst->next)
	{
		aux = env_lst;
		if (ft_strcmp(env_lst->next->name, param) == 0)
		{
			flag = 1;
			break ;
		}
		env_lst = env_lst->next;
	}
	if (flag == 0)
		return ;
	else
	{
		aux->next = env_lst->next->next;
		update_all(first_node, *env());
	}
}

void	command_unset(char **param, t_env *env_lst)
{
	int	i;

	i = 1;
	g_exit_s = 0;
	while (param[i])
	{
		unset_var(param[i], env_lst);
		i++;
	}
	free_env(env_lst);
}
