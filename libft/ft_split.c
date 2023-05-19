/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:13:23 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:10:41 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*populate(const char *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	numwords(char const *s, char c)
{
	size_t	i;
	size_t	numwords;

	numwords = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			numwords++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (numwords);
}

static char	**protectmatrix(char **matrix, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		if (!matrix[i])
		{
			while (i < j)
			{
				free(matrix[i]);
				i++;
			}
			return (NULL);
		}
		i++;
	}
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	matrix = (char **)malloc((numwords(s, c) + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < numwords(s, c))
	{
		if (s[i] && s[i] != c)
		{
			matrix[j++] = populate(&s[i], c);
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	matrix[j] = NULL;
	return (protectmatrix(matrix, j));
}
