/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:28:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:07:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	__ft_lstadd_back(t_com_list **lst, t_com_list *new)
{
	t_com_list	*current;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = __ft_lstlast(*lst);
	current->next = new;
}

int	__ft_lstsize_env(t_env *lst)
{
	int		i;
	t_env	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void	free_env2(t_env *env)
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

void	__ft_lstadd_env(t_env **env, t_env *new)
{
	t_env	*current;
	t_env	*aux;

	if (!env)
		return ;
	current = __ft_lstlast_env(*env);
	aux = *env;
	while (aux)
	{
		if (ft_strcmp(new->name, aux->name) == 0)
		{
			if (new->value)
			{
				free(aux->value);
				aux->value = ft_strdup(new->value);
			}
			free_env(new);
			return ;
		}
		aux = aux->next;
	}
	current->next = new;
}

t_com_list	*__ft_lstlast(t_com_list *lst)
{
	t_com_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (current);
}
