/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:46:32 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 20:39:37 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	count;
	int	number;
	int	sign;

	number = 0;
	count = 0;
	sign = 1;
	while ((nptr[count] == 32) || ((nptr[count] >= 9) && (nptr[count] <= 13)))
		count++;
	if ((nptr[count] == '+') || (nptr[count] == '-'))
	{
		if ((nptr[count] == '-'))
			sign = -1;
		count++;
	}
	while (ft_isdigit(nptr[count]))
	{
		number = (number * 10) + nptr[count] - 48;
		count++;
	}
	return (number * sign);
}
