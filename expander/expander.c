/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:08:31 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 16:05:23 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

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

static char	*get_var_name(char *str)
{
	char	*var_name;
	int		i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (ft_strdup(""));
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_calloc(i + 1, sizeof (char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

static char	*concat_env_to_str(char *current, char *var_name, \
int rest, char **envp)
{
	char	*env_value;
	char	*new_str;

	env_value = get_env_value(var_name, envp);
	new_str = ft_calloc(ft_strlen(env_value) + 2 + \
	ft_strlen(current) + rest + 2, sizeof (char));
	ft_strlcat(new_str, current, ft_strlen(current) + 1);
	ft_strlcat(new_str, "\"", ft_strlen(current) + 2);
	ft_strlcat(new_str, env_value, \
	ft_strlen(current) + ft_strlen(env_value) + 1 + 2);
	free(env_value);
	free(current);
	new_str[ft_strlen(new_str)] = '"';
	return (new_str);
}

static void	expander_utils(char *var_name, char *new_str, int *x, int *y)
{
	if (!new_str)
	{
		write(2, "WE COULDN'T ALLOCATE MEMORY.\n", 30);
		exit(EXIT_FAILURE);
	}
	*x += ft_strlen(var_name) + 1;
	*y = ft_strlen(new_str);
	free(var_name);
}

char	*expander(char *str, char **envp)
{
	char	*new_str;
	char	*var_name;
	int		single_quotes_len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	single_quotes_len = 0;
	new_str = ft_calloc(ft_strlen(str) + 2, sizeof (char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			single_quotes_len += jump_quotes(&str[i]);
			ft_strlcat(new_str, &str[i], ft_strlen(new_str) + single_quotes_len + 2);
			j += single_quotes_len;
			i += single_quotes_len;
		}
		else if (str[i] == '$')
		{
			var_name = get_var_name(&str[i + 1]);
			new_str = concat_env_to_str(new_str, var_name, \
			ft_strlen(&str[i + 1 + ft_strlen(var_name)]), envp);
			expander_utils(var_name, new_str, &i, &j);
		}
		else
			new_str[j++] = str[i++];
	}
	free(str);
	return (new_str);
}
