/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:18:47 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/04 12:15:25 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while ((big[i]) && (i < len))
	{
		j = 0;
		while ((big[i] != little[j]))
			i++;
		temp = i;
		while ((little[j] == big[temp]) && (temp < len))
		{
			j++;
			if (little[j] == '\0')
				return (&((char *)big)[i]);
			temp++;
		}
		i++;
	}
	return (NULL);
}
