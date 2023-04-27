/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:56 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 15:56:32 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*newstr;

	newstr = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		if (newstr[count] == (unsigned char)c)
			return (((void *)s + count));
		count++;
	}
	return (NULL);
}
