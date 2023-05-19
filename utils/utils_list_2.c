/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:00:34 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:00:53 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

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
