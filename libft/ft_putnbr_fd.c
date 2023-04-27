/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:02:10 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/07 20:59:43 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	getlength1(int n)
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

void	ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	while (i++ < getlength1(n) - 1)
		len = len * 10;
	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		ft_putchar_fd('-', fd);
	}
	while (len > 0)
	{
		ft_putchar_fd((char)(n / (len) + 48), fd);
		n = n % (len);
		len = len / 10;
	}
}
