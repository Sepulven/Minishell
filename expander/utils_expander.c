/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:29:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 23:29:11 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	char	*env_value;
	char	**matrix;

	if (!var_name || !var_name[0])
		return (ft_strdup(""));
	i = 0;
	while (envp[i])
	{
		matrix = ft_split(envp[i], '=');
		if (!matrix)
			return (NULL);
		if (ft_strncmp(var_name, matrix[0], ft_strlen(var_name)) == 0)
		{
			env_value = ft_strdup(matrix[1]);
			free_double(matrix);
			return (env_value);
		}
		else
			free_double(matrix);
		i++;
	}
	return (ft_strdup(""));
}
