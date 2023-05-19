/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_protectmatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:38:40 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:10:55 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_protectmatrix(char **matrix, size_t j)
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
