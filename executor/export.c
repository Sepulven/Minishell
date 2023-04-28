/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:01 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/28 11:39:00 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	check_repeat(t_env *var, t_env **lst)
{
	while (*lst)
	{
		if (ft_strcmp(var->name, (*lst)->name) == 0)
		{
			if (var->value)
				(*lst)->value = ft_strdup(var->value);
			else
				(*lst)->value = NULL;
			return (1);
		}
		(*lst) = (*lst)->next;
	}
	return (0);
}

void	error_m(char *command, char *param, char *str, int s)
{
	ft_putendl_fd(command, 2);
	ft_putendl_fd(param, 2);
	ft_putendl_fd(str, 2);
	g_exit_s = s;
}

void	command_export2(char *param, t_env *env_lst)
{
	t_env	*node;
	int		i;

	i = 0;
	if (param[i] == '-' && param[i + 1])
		error_m("export: `", param, "': invalid option\n", 2);
	else if (ft_isalpha(param[0]) == 0)
		error_m("export: `", param, "': not a valid identifier\n", 1);
	else
	{
		node = create_node(param);
		__ft_lstadd_env(&env_lst, node);
		update_all(env_lst, *env());
	}
}

void	export_no_p(t_env *env_lst)
{
	t_env	*aux;
	int		num_var;

	aux = env_lst;
	num_var = 0;
	while (aux)
	{
		num_var++;
		aux = aux->next;
	}
	print_env_order(env_lst, num_var);
}

void	command_export(char **param)
{
	int		i;
	t_env	*env_lst;

	i = 1;
	env_lst = get_env();
	g_exit_s = 0;
	if (!param[i])
		export_no_p(env_lst);
	else
	{
		while (param[i])
		{
			command_export2(param[i], env_lst);
			i++;
		}
	}
	free_env(env_lst);
}
