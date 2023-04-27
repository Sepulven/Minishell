/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:37:13 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 16:03:24 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*newstr;

	newstr = ft_strdup(s);
	if (!newstr)
		return (NULL);
	i = 0;
	while (newstr[i])
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	return (newstr);
}
