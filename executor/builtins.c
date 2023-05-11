/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/11 14:57:27 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

extern int	g_exit_s;

t_env	*do_node(int f, int i, t_env *node, char *str)
{
	if (f == i)
		node->value = NULL;
	else
	{
		if (!str[f + 1])
		{
			node->value = malloc(sizeof(char));
			if (!node->value)
			{
				g_exit_s = 127;
				exit(g_exit_s);
			}
			node->value[0] = '\0';
		}
		else
			node->value = ft_substr(str, f + 1, ft_strlen(str) - f);
	}
	return (node);
}

t_env	*create_node(char *str)
{
	t_env	*node;
	int		f;
	int		i;

	f = 0;
	i = 0;
	node = 0;
	node = malloc(sizeof(t_env));
	if (!node)
	{
		g_exit_s = 127;
		exit(g_exit_s);
	}
	initialize_env(&node);
	while (str[i] && str[i] != 61)
	{
		i++;
		f++;
	}
	while (str[i])
		i++;
	node->name = ft_substr(str, 0, f);
	return (do_node(f, i, node, str));
}

void	check_builtin(int **fd, t_command_list *lst, int com)
{
	int		flag;
	t_env	*aux;

	aux = get_env();
	flag = 0;
	if (ft_strcmp(lst->command, "export") == 0)
		command_export(lst->param);
	else if (ft_strcmp(lst->command, "pwd") == 0)
		command_pwd(get_env());
	else if (ft_strcmp(lst->command, "env") == 0)
		command_env(lst->param);
	else if (ft_strcmp(lst->command, "echo") == 0)
		command_echo(lst->param);
	else if (ft_strcmp(lst->command, "cd") == 0)
		command_cd(lst->param, aux);
	else if (ft_strcmp(lst->command, "exit") == 0)
		command_exit(lst);
	else if (ft_strcmp(lst->command, "unset") == 0)
		command_unset(lst->param);
	else
		flag = -1;
	free_env(aux);
	if (flag == 0)
	{
		free_envp(*env());
		free_lst(lst);
		if (fd)
			free_pipes(fd, com);
		exit(g_exit_s);
	}
}

int	check_builtin_one(t_command_list *lst)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(lst->command, "export") == 0)
		command_export(lst->param);
	else if (ft_strcmp(lst->command, "cd") == 0)
		command_cd(lst->param, get_env());
	else if (ft_strcmp(lst->command, "exit") == 0)
		command_exit(lst);
	else if (ft_strcmp(lst->command, "unset") == 0)
		command_unset(lst->param);
	else
		flag = -1;
	return (flag);
}
