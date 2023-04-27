/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:24:18 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 20:57:57 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	while (src[i] && j < (size - 1))
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
