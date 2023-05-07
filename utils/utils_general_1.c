/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 02:22:59 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/07 13:52:25 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	ft_swap(char *x, char *y)
{
	char	tmp;

	tmp = *y;
	*y = *x;
	*x = tmp;
}

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
