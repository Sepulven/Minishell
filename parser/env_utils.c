/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:49:19 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 14:56:23 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

static char	*get_aux(const char *big, const char *little)
{
	size_t	count;
	size_t	a;

	count = 0;
	if (!little[0] || !little)
		return ((char *)big);
	while (little && count < ft_strlen(big))
	{
		a = 0;
		while (big[count + a] == little[a] && big)
		{
			a++;
			if (little[a] == '\0' && big[count + a] == '='
				&& big[0] == little[0])
				return ((char *)big + count + ft_strlen(little) + 1);
		}
		count++;
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*aux;

	i = 0;
	paths = 0;
	while (envp[i])
	{
		aux = get_aux(envp[i], "PATH");
		if (aux)
			paths = ft_split(aux, ':');
		i++;
	}
	return (paths);
}

char	*check_path(char **paths, char *command)
{
	int		i;
	char	*path1;
	char	*path2;

	i = 0;
	if (!paths)
		return (ft_strdup(command));
	while (paths[i])
	{
		path1 = ft_strjoin(paths[i], "/");
		path2 = ft_strjoin(path1, command);
		free(path1);
		if (path2 && access(path2, X_OK) == 0)
			return (path2);
		free(path2);
		i++;
	}
	return (ft_strdup(command));
}
