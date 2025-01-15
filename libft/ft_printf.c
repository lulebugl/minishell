/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:34:45 by llebugle          #+#    #+#             */
/*   Updated: 2024/11/05 11:56:13 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	print_unsigned(unsigned int nb)
{
	size_t	len;

	len = 0;
	if (nb > 9)
	{
		len += print_unsigned((nb / 10));
		len += print_unsigned((nb % 10));
	}
	else
	{
		ft_putchar_fd(nb + 48, 1);
		len++;
	}
	return (len);
}

static size_t	print_hex(unsigned long long n, char *base)
{
	size_t	len;

	len = 0;
	if (n > 15)
	{
		len += print_hex(n / 16, base);
		len += print_hex(n % 16, base);
	}
	else
	{
		ft_putchar_fd(base[n], 1);
		len++;
	}
	return (len);
}

static size_t	print_pointer(unsigned long long p)
{
	size_t	len;

	len = 0;
	if (!p)
		return (write(1, "(nil)", 5), 5);
	write(1, "0x", 2);
	len += print_hex(p, "0123456789abcdef");
	return (len + 2);
}

static size_t	print_arg(va_list args, char c)
{
	if (!c)
		return (0);
	if (c == '%')
		return (ft_putchar_fd('%', 1), 1);
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	else if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (c == 'd')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (c == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (print_pointer(va_arg(args, unsigned long long)));
	else if (c == 'x')
		return (print_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (print_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += print_arg(args, *(format + 1));
			format++;
		}
		else
		{
			ft_putchar_fd(*format, 1);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}
