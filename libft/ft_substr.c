/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:09:03 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/03 12:59:06 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (!len || ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) - start > len)
		str = (char *) malloc(len + 1);
	else
		str = (char *) malloc(ft_strlen(s) - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = (char)s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
