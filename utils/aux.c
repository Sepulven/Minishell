/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:02:08 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 19:38:13 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

char	**dup_env(char **envp)
{
	int		i;
	int		count;
	char	**env;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	env = ft_calloc(sizeof(char *), count + 1);
	if (!env)
		return (NULL);
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	free_envp(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
}

char	*ft_substr_mini(char const *s, unsigned int start, unsigned int end)
{
	char			*ptr;
	unsigned int	a;
	unsigned int	len;

	a = 0;
	len = end - start;
	ptr = malloc(((int)len + 1) * sizeof(char));
	if (!ptr || !s)
		return (NULL);
	while (start < end)
	{
		ptr[a] = s[start];
		a++;
		start++;
	}
	ptr[a] = '\0';
	if (check_words(ptr) == 0)
		return (NULL);
	return (ptr);
}

int	ft_strcmp_mini(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] || b[i])
	{
		if (a[i] != b[i])
			return (-1);
		i++;
	}
	return (1);
}
