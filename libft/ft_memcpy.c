/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:39:55 by asepulve          #+#    #+#             */
/*   Updated: 2022/10/28 15:47:19 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return ((void *) dest);
}
