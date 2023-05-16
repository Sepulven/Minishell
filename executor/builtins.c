/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/16 11:59:18 by mvicente         ###   ########.fr       */
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

void	exit_builtins(t_com_list *lst, int **fd, int com)
{
	if (*env())
		free_envp(*env());
	free_lst(lst);
	if (fd)
		free_pipes(fd, com);
	exit(g_exit_s);
}

void	builtins(t_com_list *lst, int **fd, t_com_list *node, int com)
{
	int		flag;

	flag = 0;
	if (ft_strcmp(node->command, "export") == 0)
		command_export(node->param);
	else if (ft_strcmp(node->command, "pwd") == 0)
		command_pwd(node->param);
	else if (ft_strcmp(node->command, "env") == 0)
		command_env(node->param);
	else if (ft_strcmp(node->command, "echo") == 0)
		command_echo(node->param);
	else if (ft_strcmp(node->command, "cd") == 0)
		command_cd(node->param);
	else if (ft_strcmp(node->command, "exit") == 0)
		command_exit(node);
	else if (ft_strcmp(node->command, "unset") == 0)
		command_unset(node->param);
	else
		flag = -1;
	if (flag == 0)
		exit_builtins(lst, fd, com);
}

int	check_builtin_one(t_com_list *lst)
{
	int		flag;

	flag = 0;
	if (ft_strcmp(lst->command, "export") == 0)
		command_export(lst->param);
	else if (ft_strcmp(lst->command, "cd") == 0)
		command_cd(lst->param);
	else if (ft_strcmp(lst->command, "exit") == 0)
		command_exit(lst);
	else if (ft_strcmp(lst->command, "unset") == 0)
		command_unset(lst->param);
	else
		flag = -1;
	return (flag);
}
