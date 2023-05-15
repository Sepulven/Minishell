/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:03:11 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/15 18:23:01 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

t_env	*fetch_node(t_env *env_lst, char *name)
{
	int	len;

	len = ft_strlen(name);
	while (env_lst)
	{
		if (ft_strncmp(env_lst->name, name, len) == 0)
			return (env_lst);
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*get_strlist(t_env *env_lst, char *aux)
{
	char	*str_list;

	str_list = NULL;
	if (env_lst->value)
		str_list = ft_strjoin(aux, env_lst->value);
	else
		str_list = ft_strdup(env_lst->name);
	return (str_list);
}

char	*get_newenv(char **envp, char *str_lst, int i)
{
	char	*str;

	str = NULL;
	if (envp[i] && ft_strcmp(str_lst, envp[i]) == 0)
		str = ft_strdup(envp[i]);
	else
		str = ft_strdup(str_lst);
	return (str);
}

void	update_all(t_env *env_lst, char **envp)
{
	int		i;
	char	**new_env;
	char	*str_list;
	char	*aux;

	i = 0;
	new_env = ft_calloc(__ft_lstsize_env(env_lst) + 1, sizeof (char *));
	str_list = NULL;
	while (env_lst)
	{
		aux = ft_strjoin(env_lst->name, "=");
		str_list = get_strlist(env_lst, aux);
		new_env[i] = get_newenv(envp, str_list, i);
		free(aux);
		free(str_list);
		i++;
		if (!env_lst->next)
			break ;
		env_lst = env_lst->next;
	}
	free_double(envp);
	*env() = new_env;
}

void	update_var(t_env *env_lst, char *oldpwd)
{
	t_env	*aux;
	char	pwd[1024];

	aux = NULL;
	aux = fetch_node(env_lst, "PWD");
	if (aux)
		aux->value = getcwd(pwd, sizeof(pwd));
	aux = fetch_node(env_lst, "OLDPWD");
	if (aux)
		aux->value = oldpwd;
	update_all(env_lst, *env());
}
