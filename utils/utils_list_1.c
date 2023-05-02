/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:28:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/02 12:27:53 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	__ft_lstadd_back(t_command_list **lst, t_command_list *new)
{
	t_command_list	*current;

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

void	__ft_lstadd_env(t_env **env, t_env *new)
{
	t_env	*current;
	t_env	*aux;

	if (!env)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	current = __ft_lstlast_env(*env);
	aux = *env;
	while (aux)
	{
		if (ft_strcmp(new->name, aux->name) == 0)
		{
			if (new->value)
				aux->value = ft_strdup(new->value);
			else
				aux->value = NULL;
			return ;
		}
		aux = aux->next;
	}
	current->next = new;
}

t_command_list	*__ft_lstlast(t_command_list *lst)
{
	t_command_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (current);
}

t_env	*__ft_lstlast_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (current);
}
