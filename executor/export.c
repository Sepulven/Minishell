/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:01 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/15 17:23:33 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

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

void	command_export2(char *param, t_env *env_lst)
{
	t_env	*node;
	int		i;

	i = 0;
	if (check_flags_one(param, "export") == -1)
		return ;
	else if (ft_isalpha(param[0]) == 0)
		error_m("export", param, "not a valid identifier\n", 1);
	else
	{
		while (param[i] && param[i] != '=')
		{
			if (ft_isalnum(param[i]) == 0 && param[i] != '_')
			{
				error_m("export", param, "not a valid identifier\n", 1);
				return ;
			}
			i++;
		}
		node = create_node(param);
		__ft_lstadd_env(&env_lst, node);
		update_all(env_lst, *env());
	}
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
