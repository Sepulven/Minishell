/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:02:44 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/04 18:59:48 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*s;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strrchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1);
	while (i > start && ft_strrchr(set, s1[i - 1]))
		i--;
	end = i;
	s = ft_substr(s1, start, end - start);
	return (s);
}
