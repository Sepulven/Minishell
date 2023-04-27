/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:54:26 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 15:56:51 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*newstr1;
	unsigned char	*newstr2;

	count = 0;
	newstr1 = (unsigned char *)s1;
	newstr2 = (unsigned char *)s2;
	while (count < n)
	{
		if (newstr1[count] != newstr2[count])
			return (newstr1[count] - newstr2[count]);
		count++;
	}
	return (0);
}
