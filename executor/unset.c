/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/16 13:49:38 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

int	check_param(char *param)
{
	int	i;

	i = 0;
	if (check_flags_one(param, "unset") == -1)
		return (-1);
	while (param[i])
	{
		if (param[i] == '=' || ft_isalnum(param[i]) == 0)
		{
			error_m("unset", param, "not a valid identifier\n", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_env	*loop_lst(int *flag, t_env **lst, char *param)
{
	t_env	*aux;

	while ((*lst) && (*lst)->next)
	{
		aux = (*lst);
		if (ft_strcmp((*lst)->next->name, param) == 0)
		{
			*flag = 1;
			break ;
		}
		(*lst) = (*lst)->next;
	}
	return (aux);
}

void	free_node(t_env*node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	unset_var(char *param, t_env *env_lst)
{
	t_env	*first_node;
	int		flag;
	t_env	*aux;
	t_env	*node_to_free;

	first_node = env_lst;
	flag = 0;
	if (check_param(param) == -1)
	{
		g_exit_s = 1;
		return ;
	}
	aux = loop_lst(&flag, &env_lst, param);
	node_to_free = aux->next;
	if (flag == 0)
		return ;
	else
	{
		aux->next = env_lst->next->next;
		free_node(node_to_free);
		update_all(first_node, *env());
	}
}

void	command_unset(char **param)
{
	int		i;
	t_env	*env_lst;
	t_env	*aux;

	i = 1;
	env_lst = get_env();
	aux = env_lst;
	g_exit_s = 0;
	while (param[i])
	{
		unset_var(param[i], env_lst);
		i++;
	}
	free_env(aux);
}
