/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:28:55 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 15:56:07 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	getlength(int n)
{
	size_t	length;

	length = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*convert(char *str, size_t sign, int n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (i++ < getlength(n) - 1)
		len = len * 10;
	i = 0;
	if (sign)
		str[i++] = '-';
	while (len > 0)
	{
		str[i++] = n / (len) + 48;
		n = n % (len);
		len = len / 10;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	sign;
	char	*str;

	if (n == -2147483648)
	{
		str = (char *)malloc(12);
		if (!str)
			return (NULL);
		return (ft_memcpy(str, "-2147483648\0", 12));
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = n * (-1);
	}
	str = (char *)malloc(getlength(n) + sign + 1);
	if (!str)
		return (NULL);
	return (convert(str, sign, n));
}
