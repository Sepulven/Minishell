/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:35:54 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/06 23:10:02 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	printf_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	ft_printf("\n\n");
}

t_env	*lst_delete(t_env *lst, char *node_del)
{
	t_env	*new_lst;
	t_env	*aux;

	new_lst = lst;
	if (ft_strcmp(lst->name, node_del) == 0)
	{
		lst = lst->next;
		return (lst);
	}
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->next->name, node_del) == 0)
		{
			aux = lst->next->next;
			free(lst->next->name);
			if (lst->next->value)
				free(lst->next->value);
			free(lst->next);
			lst->next = aux;
			lst = new_lst;
			return (lst);
		}
		lst = lst->next;
	}
	return (new_lst);
}

void	print_env_order(t_env *env_lst, int num_var)
{
	int		f;
	t_env	*aux;
	t_env	*node;

	f = 0;
	aux = env_lst;
	while (f < num_var)
	{
		node = env_lst;
		while (env_lst && env_lst->next)
		{
			if (ft_strcmp(node->name, env_lst->next->name) > 0)
				node = env_lst->next;
			env_lst = env_lst->next;
		}
		if (!node->value)
			ft_printf("declare -x %s\n", node->name);
		else if (ft_strlen(node->value) == 0)
			ft_printf("declare -x %s=''\n", node->name);
		else if (node->value)
			ft_printf("declare -x %s=%s\n", node->name, node->value);
		env_lst = lst_delete(aux, node->name);
		aux = env_lst;
		f++;
	}
}
