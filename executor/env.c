/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:44:17 by asepulve          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/27 23:57:23 by asepulve         ###   ########.fr       */
=======
/*   Updated: 2023/04/28 11:26:56 by mvicente         ###   ########.fr       */
>>>>>>> de98a0f8795563a3b0527cb5f0da32accc053f43
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

void	free_env(t_env *env)
{
	t_env	*ptr;

	while (env)
	{
		ptr = env->next;
		free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = ptr;
	}
}

void	command_env(char **param)
{
	t_env	*env;
	t_env	*aux;

	g_exit_s = 0;
	if (param[1])
	{
		no_file_message("env", param[1], 127);
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
