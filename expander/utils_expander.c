/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:29:00 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:15:46 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

int	ft_isvar(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '$' || !(ft_isalnum(str[i]) \
	|| str[i] == '_' || str[i] == '?'))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	if (i <= 1 && (ft_isdigit(str[1]) || str[i] == '_'))
		return (0);
	return (1);
}

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	char	*env_value;
	char	**matrix;

	if (!var_name || !var_name[0])
		return (ft_strdup(""));
	i = 0;
	env_value = NULL;
	while (envp[i])
	{
		matrix = ft_split(envp[i], '=');
		if (ft_strncmp(var_name, matrix[0], ft_strlen(var_name)) == 0)
		{
			if (!matrix[1])
				env_value = ft_strdup("");
			else
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
