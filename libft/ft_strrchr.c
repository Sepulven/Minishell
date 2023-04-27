/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:45:43 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 16:04:03 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	int		len;

	len = ft_strlen(s);
	temp = (char *)s;
	while (temp[len] != (char)c && len != 0)
		len--;
	if (temp[len] == (char)c)
		return (&temp[len]);
	return (NULL);
}
