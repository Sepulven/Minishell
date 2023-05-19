/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:48:17 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/19 19:49:41 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

void	command_env(char **param)
{
	t_env	*env;
	t_env	*aux;

	g_exit_s = 0;
	if (param[1])
	{
		if (check_flags_two(param, "env") == -1)
			return ;
		error_m("env", param[1], "No such file or directory\n", 127);
		return ;
	}
	env = get_env();
	aux = env;
	while (env)
	{
		if (env->value)
			ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	free_env(aux);
}

void	initialize_env(t_env **new)
{
	(*new)->name = 0;
	(*new)->value = 0;
	(*new)->next = 0;
}

t_env	*get_env(void)
{
	int		i;
	char	**envp;
	t_env	*env_lst;
	t_env	*aux;

	i = 0;
	g_exit_s = 0;
	envp = *env();
	env_lst = create_node(envp[i]);
	i++;
	while (envp[i])
	{
		aux = create_node(envp[i]);
		__ft_lstadd_env(&env_lst, aux);
		i++;
	}
	return (env_lst);
}
