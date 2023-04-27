/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:01:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/04/27 12:11:19 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

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

void	check_builtin(t_command_list *lst)
{
	if (ft_strcmp(lst->command, "cd") == 0)
		exit(0);
	else if (ft_strcmp(lst->command, "export") == 0)
	{
		command_export(lst->param);
		exit(g_exit_s);
	}
	else if (ft_strcmp(lst->command, "unset") == 0)
		exit(0);
	else if (ft_strcmp(lst->command, "exit") == 0)
		exit(0);
	else if (ft_strcmp(lst->command, "pwd") == 0)
	{
		command_pwd(get_env());
		exit(g_exit_s);
	}
	else if (ft_strcmp(lst->command, "env") == 0)
	{
		command_env(lst->param);
		exit(g_exit_s);
	}
}

int	check_builtin_one(t_command_list *lst)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(lst->command, "cd") == 0)
		command_cd(lst->param, get_env());
	else if (ft_strcmp(lst->command, "export") == 0)
		command_export(lst->param);
	else if (ft_strcmp(lst->command, "unset") == 0)
		command_unset(lst->param, get_env());
	else if (ft_strcmp(lst->command, "exit") == 0)
		command_exit(lst);
	else if (ft_strcmp(lst->command, "pwd") == 0)
		command_pwd(get_env());
	else if (ft_strcmp(lst->command, "env") == 0)
		command_env(lst->param);
	else if (ft_strcmp(lst->command, "echo") == 0)
		command_echo(lst->param);
	else
		flag = -1;
	// if (flag == 0)
	// 	printf("status %i\n", g_exit_s);
	return (flag);
}
