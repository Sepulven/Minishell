/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:20:13 by asepulve          #+#    #+#             */
/*   Updated: 2023/03/11 16:46:10 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putnbr_basel(long long nbr, char *base, int size)
{
	if (nbr < 0)
		return (write(1, "-", 1) + ft_putnbr_basel(nbr * -1, base, size));
	if (nbr < size)
		return (write(1, &base[nbr], 1));
	else
		return (ft_putnbr_basel(nbr / size, base, size)
			+ write(1, &base[nbr % size], 1));
	return (0);
}

static size_t	ft_putnbrull_basel(unsigned long long nbr, char *base, int size)
{
	if (nbr < (unsigned long long)size)
		return (write(1, &base[nbr], 1));
	else
		return (ft_putnbrull_basel(nbr / size, base, size)
			+ write(1, &base[nbr % size], 1));
	return (0);
}

static size_t	pointercase(va_list arg)
{
	long long	pointer;

	pointer = va_arg(arg, unsigned long long);
	if (pointer == 0)
		return (write(1, "(nil)", 5));
	else
		return (write(1, "0x", 2)
			+ ft_putnbrull_basel(pointer, L_HEXDECIMAL, 16));
	return (0);
}

static size_t	conversion(char convertor, va_list arg )
{
	void	*p;

	if (convertor == 's')
	{
		p = va_arg(arg, char *);
		if (!p)
			return (write(1, "(null)", 6));
		return (write(1, p, ft_strlen((char *)p)));
	}
	if (convertor == 'p')
		return (pointercase(arg));
	if (convertor == 'd' || convertor == 'i')
		return (ft_putnbr_basel(va_arg(arg, int), DECIMAL, 10));
	if (convertor == 'u')
		return (ft_putnbr_basel(va_arg(arg, unsigned int), DECIMAL, 10));
	if (convertor == 'x')
		return (ft_putnbr_basel(va_arg(arg, unsigned int), L_HEXDECIMAL, 16));
	if (convertor == 'X')
		return (ft_putnbr_basel(va_arg(arg, unsigned int), U_HEXDECIMAL, 16));
	if (convertor == 'c')
	{
		convertor = va_arg(arg, int);
		return (write(1, &convertor, 1));
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_prt;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(arg_prt, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
				len += write(1, "%", 1);
			else
				len += conversion(format[i + 1], arg_prt);
			i += 2;
		}
		else
			len += write(1, &format[i++], 1);
	}
	va_end(arg_prt);
	return (len);
}
